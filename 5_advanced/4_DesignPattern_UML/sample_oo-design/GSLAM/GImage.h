// GSLAM - A general SLAM framework and benchmark
// Copyright 2018 PILAB Inc. All rights reserved.
// https://github.com/zdzhaoyong/GSLAM
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: zd5945@126.com (Yong Zhao)
//
// GImage provides seemlessly copy and basic functions of cv::Mat

#ifndef GSLAM_GIMAGE_H
#define GSLAM_GIMAGE_H
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <atomic>

#if defined(HAS_OPENCV) || defined(HAS_OPENCV3)
#include <opencv2/core/core.hpp>
#else
typedef unsigned char uchar;
#endif

#ifndef CV_XADD
  #include <mutex>
  static inline int CV_XADD(int* addr, int delta)
  {
      static std::mutex mutex;
      std::unique_lock<std::mutex> lock(mutex);
      int tmp = *addr; *addr += delta; return tmp;
  }
#endif

namespace GSLAM{

#ifndef DOXYGEN_IGNORE_INTERNAL

enum GElementType{
    GElementType_8U =0,
    GElementType_8S =1,
    GElementType_16U=2,
    GElementType_16S=3,
    GElementType_32S=4,
    GElementType_32F=5,
    GElementType_64F=6,
    GElementType_UserType=7
};

template <typename C>
class GElement
{
public:
    enum{Type=GElementType_UserType};
};

template <>
class GElement<uint8_t>
{
public:
    enum{Type=GElementType_8U};
};

template <>
class GElement<char>
{
public:
    enum{Type=GElementType_8S};
};

template <>
class GElement<int16_t>
{
public:
    enum{Type=GElementType_16S};
};

template <>
class GElement<uint16_t>
{
public:
    enum{Type=GElementType_16U};
};

template <>
class GElement<int32_t>
{
public:
    enum{Type=GElementType_32S};
};

template <>
class GElement<float>
{
public:
    enum{Type=GElementType_32F};
};

template <>
class GElement<double>
{
public:
    enum{Type=GElementType_64F};
};

template <typename EleType=uint8_t,int channelSize=1>
struct GImageType
{
    enum{Type=((GElement<EleType>::Type&0x7)+((channelSize-1)<<3))};
};

struct UMatData// for OpenCV Version 3
{
    enum { COPY_ON_MAP=1, HOST_COPY_OBSOLETE=2,
        DEVICE_COPY_OBSOLETE=4, TEMP_UMAT=8, TEMP_COPIED_UMAT=24,
        USER_ALLOCATED=32, DEVICE_MEM_MAPPED=64};
    const void* prevAllocator;
    const void* currAllocator;
    int urefcount;
    int refcount;
    uchar* data;
    uchar* origdata;
    size_t size;

    int flags;
    void* handle;
    void* userdata;
    int allocatorFlags_;
    int mapcount;
    UMatData* originalUMatData;
};
#endif

/**
 * @brief The GImage class is a tiny implementation of image for removing dependency of opencv.
 * Most APIs are corrosponding to "cv::Mat".
 */
class GImage
{
public:
    GImage()
        :cols(0),rows(0),flags(0),data(NULL),refCount(NULL)
    {

    }

    GImage(int rows_,int cols_,int type=GImageType<>::Type,uchar* src=NULL,bool copy=false,int imageAlign=16)
        :cols(cols_),rows(rows_),flags(type),data(NULL),refCount(NULL)
    {
        if(src&&!copy)
        {
            data=src;
            return;
        }

        int byteNum=total()*elemSize();
        if(byteNum<=0) return;
        int alignBytes=alignSize(byteNum, (int)sizeof(*refCount));
        data=(uchar*)fastMalloc(alignBytes+sizeof(int*),imageAlign);
        if(!data)
        {
            cols=0;rows=0;return ;
        }
        refCount=(int*)(data+alignBytes);
        *refCount=1;
        if(src)
            memcpy(data,src,byteNum);
    }

    GImage(const GImage& ref)
        : cols(ref.cols),rows(ref.rows),flags(ref.flags),
          data(ref.data),refCount(ref.refCount)
    {
        if(refCount)
            CV_XADD(refCount,1);
    }

    ~GImage()
    {
        if(data&&refCount)
        {
            if(CV_XADD(refCount,-1)==1)
            {
                release();
            }
        }
        cols=rows=flags=0;
        data=NULL;
        refCount=NULL;
    }

    // This is not thread safe when GImage not empty!
    GImage& operator=(const GImage& rhs)
    {
        this->~GImage();
        cols=rhs.cols;
        rows=rhs.rows;
        flags=rhs.flags;
        data=rhs.data;
        refCount=rhs.refCount;
        if(refCount) CV_XADD(refCount,1);
        return *this;
    }

    static GImage create(int rows,int cols,int type=GImageType<>::Type,uchar* src=NULL,bool copy=false,int imageAlign=16)
    {
        return GImage(rows,cols,type,src,copy);
    }

    static GImage zeros(int rows,int cols,int type=GImageType<>::Type,uchar* src=NULL,bool copy=false,int imageAlign=16)
    {
        GImage result(rows,cols,type,src,copy,imageAlign);
        memset(result.data,0,result.total()*result.elemSize());
        return result;
    }

    bool empty()const{return !data;}
    int  elemSize()const{return channels()*elemSize1();}
    int  elemSize1()const{return (1<<((type()&0x7)>>1));}

    int  channels()const{return (type()>>3)+1;}
    int  type()const{return flags;}
    int  total()const{return cols*rows;}

    GImage clone()const
    {
        return GImage(rows,cols,flags,data,true);
    }

    template <typename C>
    C& at(int idx){return ((C*)data)[idx];}

    template <typename C>
    C& at(int ix,int iy){return ((C*)data)[iy*cols+ix];}


#if defined(HAS_OPENCV) || defined(HAS_OPENCV3)
#if CV_VERSION_EPOCH == 2
    inline operator cv::Mat()const
    {
        if(empty()) return cv::Mat();
        cv::Mat result(rows,cols,type(),data);
        if(refCount)
        {
            result.refcount=refCount;
            CV_XADD(refCount,1);
        }
        return result;
    }
    GImage(const cv::Mat& mat)
        : cols(mat.cols),rows(mat.rows),flags(mat.type()),
          data(mat.data),refCount(mat.refcount)
    {
        if(refCount) CV_XADD(refCount,1);
    }
#elif CV_VERSION_MAJOR == 3
    inline operator cv::Mat()const
    {
        if(!data) return cv::Mat();
        cv::Mat result(rows,cols,type(),data);
        int byteNum=total()*elemSize();
        int alignBytes=alignSize(byteNum, (int)sizeof(*refCount));
        if(((uchar*)refCount)==data+alignBytes)// OpenCV2 style => OpenCV3 style
        {
            // WARNING: MAKE SURE THERE ARE NO OTHER HOLDERS
            // construct a UMat that ref to data
            cv::UMatData* u=new cv::UMatData(cv::Mat::getStdAllocator());
            u->data=data;
#if CV_VERSION_MINOR>=3
            u->origdata=((uchar**)data)[-1];
#else
            u->origdata=data;
#endif
            u->userdata=refCount;
            CV_XADD(refCount,1); // Now we have both refcount and both added 1
            u->refcount=2;
//            u->flags|=cv::UMatData::USER_ALLOCATED;
            refCount=&u->refcount;
            result.u=u;
//            result.allocator=nullptr;
            return result;
        }
        else // OpenCV3 style => OpenCV3 style
        {
            CV_XADD(refCount,1);
            cv::UMatData* u=(cv::UMatData*)(((uchar*)refCount)-sizeof(int)-sizeof(cv::MatAllocator*)*2);
            result.u=u;
            return result;
        }
        return result;// no copy but not safe either
    }

    GImage(const cv::Mat& mat)
        : cols(mat.cols),rows(mat.rows),flags(mat.type()),
          data(mat.data),refCount(NULL)
    {
        if(mat.u&&mat.u->currAllocator==cv::Mat::getStdAllocator())
            // try to maintain the refcount things, but this need the mat is allocated by default StdAllocator
        {
            refCount=(&mat.u->refcount);
            CV_XADD(refCount,1);
        }
        else if(0)// copy the data: SAFE but SLOW
        {
            int byteNum=total()*elemSize();
            data=(uchar*)fastMalloc(byteNum+sizeof(int*));
            if(!data)
            {
                cols=0;rows=0;return ;
            }
            refCount=(int*)(data+byteNum);
            *refCount=1;
            if(mat.data)
                memcpy(data,mat.data,byteNum);
        }
    }
#endif

#endif

    void release()
    {
        size_t totalBytes=total()*elemSize();
        int alignBytes=alignSize(totalBytes, (int)sizeof(*refCount));
        if(refCount==((int*)(data+alignBytes))) // OpenCV2 style
        {
            cols=rows=0;
            fastFree(data);
            refCount=NULL;
            data=NULL;
        }
        else// OpenCV3 style
        {
            UMatData* u=(UMatData*)(((uchar*)refCount)-offsetof(UMatData,refcount));
            if(u->userdata==data+alignBytes)
            {
                // this is allocated by GImage, we need minus both refcount
                refCount=(int*)u->userdata;
                if(CV_XADD(refCount,-1)==1)
                {
                    return release();
                }
            }
            else{
                // allocated by OpenCV
                assert(u->size==totalBytes);
                //assert(u->currAllocator==NULL);// should be the default allocator
                deallocate(u);
            }
            cols=rows=0;
            refCount=NULL;
            data=NULL;
        }
    }

    template<typename _Tp> _Tp* ptr(int i0=0){return (_Tp*)(data+i0*cols*elemSize());}

    template<typename _Tp> const _Tp* ptr(int i0=0) const{return (_Tp*)(data+i0*cols*elemSize());}

    const GImage row(int idx=0)const{return GImage(1,cols,type(),data+elemSize()*cols*idx);}

    int getWidth()const{return cols;}
    int getHeight()const{return rows;}

private:

    template<typename _Tp> static inline _Tp* alignPtr(_Tp* ptr, int n=(int)sizeof(_Tp))
    {
        return (_Tp*)(((size_t)ptr + n-1) & -n);
    }

    void* fastMalloc( size_t size ,int imageAlign=16) const
    {
        uchar* udata = (uchar*)malloc(size + sizeof(void*) + imageAlign);
        if(!udata)
            return NULL;
        uchar** adata = alignPtr((uchar**)udata + 1, imageAlign);
        adata[-1] = udata;
        return adata;
    }

    void fastFree(void* ptr) const
    {
        if(ptr)
        {
            uchar* udata = ((uchar**)ptr)[-1];
            free(udata);
        }
    }

    static inline size_t alignSize(size_t sz, int n)
    {
        assert((n & (n - 1)) == 0); // n is a power of 2
        return (sz + n-1) & -n;
    }

    void deallocate(UMatData* u) const// for OpenCV Version 3
    {
        if(!u)
            return;

        assert(u->urefcount == 0);
        assert(u->refcount == 0);
        if( !(u->flags & UMatData::USER_ALLOCATED) )
        {
            uchar* udata = ((uchar**)u->origdata)[-1];
            int n=u->origdata-udata;
            if((n & (n - 1)) == 0&&n>=0&&n<=32){
                fastFree(u->origdata);
            }
            else free(u->origdata);
            u->origdata = 0;
        }
        delete u;
    }

public:
    int  cols,rows,flags;
    uchar*          data;
    mutable int*    refCount;
};

}
#endif

