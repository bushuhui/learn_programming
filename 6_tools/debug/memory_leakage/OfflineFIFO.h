#ifndef __OFFLINE_FIFO_H__
#define __OFFLINE_FIFO_H__

//#define HAS_LZ4
//#define HAS_UTILS_FS

#include <stdint.h>
#include <stdio.h>

#include <string>
#include <deque>
#include <thread>
#include <vector>

#include <GSLAM/core/SPtr.h>
#include <GSLAM/core/Svar.h>
#include <GSLAM/core/Timer.h>
#include <GSLAM/core/Mutex.h>

#ifdef HAS_UTILS_FS
#include "utils_fs.h"
#endif

#ifdef HAS_LZ4
#include "utils_lz4.h"
#endif

typedef std::lock_guard<GSLAM::Mutex> ScopedLock;
typedef SPtr<std::vector<uint8_t> > BuffType;

/**
 * Offline FIFO class
 *
 * This class will automatically save buffer item to disk,
 * when the queue size execeed given `writeThreshold`
 * When pop the item in the queue, this class will automaticall load save data from disk
 *
 */
class OfflineFifo
{
protected:
    struct Item
    {
        BuffType        buf;                // buffer array

        int             id;                 // id number
        int             offline;            // 0 - not offline (in memory),
                                            // 1 - offline (save to disk)
    };

    typedef SPtr<Item> SItem;

public:
    /**
     * @brief OfflineFifo
     *
     * @param tempPath              [in] temp buffer dir name and file prefix name
     * @param writeThreshold        [in] when queue size exceed the value,
     *                                   new push item will be save to disk
     */
    OfflineFifo(const std::string& tempPath = "./ob", int writeThreshold=20)
        :_tempPath(tempPath), _writeThreshold(writeThreshold), _uid(0), _shouldStop(false), _readAhead(10)
    {
        // max queue size
        _maxQueueSize = 1000;

        // start write/read threads
        _threadWrite = std::thread(&OfflineFifo::offlineWrite, this);
        _threadRead  = std::thread(&OfflineFifo::offlineRead,  this);

        // create temp dir if not exist
        createTemps();
    }

    ~OfflineFifo()
    {
        stop();
        removeTemps();

        //_buff.clear();
        //_buffWrite.clear();

        printf("OfflineFifo::~OfflineFifo\n");
    }


    int push(BuffType& buf)
    {
        SItem item = SItem(new Item());
        item->id = _uid++;
        item->offline = 0;
        item->buf = buf;

        // push to FIFO
        {
            ScopedLock mu(_mutexQueue);

            _buff.push_back(item);
        }

        // if FIFO exceed given size, then backup data to file
        if( _buff.size() > _writeThreshold )
        {
            ScopedLock mu2(_mutexWrite);

            _buffWrite.push_back(item);
        }

        // if queue size is too large, then remove some items
        if( _buff.size() > _maxQueueSize )
        {
            while( _buff.size() > _maxQueueSize )
            {
                BuffType bt = pop();
            }
        }

        return 0;
    }


    BuffType pop(void)
    {
        SItem item;
        ScopedLock mu(_mutexQueue);

        // get first item
        if( _buff.size() > 0 )
        {
            item = _buff.front();
            _buff.pop_front();
        }
        else
        {
            return BuffType();
        }

        if( item->offline ) itemLoad(item);
        return item->buf;
    }

    /**
     * @brief get the current queue size
     *
     * @return queue item number
     */
    int size(void)
    {
        ScopedLock mu(_mutexQueue);

        return _buff.size();
    }

    /**
     * @brief stop the FIFO system
     *
     * @return
     */
    int stop(void)
    {
        _shouldStop = true;
        while( !_threadRead.joinable() || !_threadWrite.joinable() )
            GSLAM::Rate::sleep(0.01);

        _threadWrite.join();
        _threadRead.join();

        return 0;
    }

    /**
     * @brief setQueueMaxSize
     * @param maxsize           - [in] queue size
     * @return
     */
    int setQueueMaxSize(int maxsize)
    {
        _maxQueueSize = maxsize;
    }

    /**
     * @brief getQueueMaxSize
     * @return
     */
    int getQueueMaxSize(void)
    {
        return _maxQueueSize;
    }


    /**
     * @brief Create temp dir
     *
     * @return
     */
    int createTemps(void)
    {
#ifdef HAS_UTILS_FS
        std::string p = utils_fs::path_getPathName(_tempPath);
        if( p.size() > 0 ) utils_fs::path_mkdir(p);
#endif

        return 0;
    }

    /**
     * @brief Remove all temp files & directory
     *
     * @return
     */
    int removeTemps(void)
    {
        // remove all files in temp data dir
#ifdef HAS_UTILS_FS
        std::string p = utils_fs::path_getPathName(_tempPath);
        if( p.size() > 0 )
        {
            utils_fs::path_rmdir(p);
            utils_fs::path_mkdir(p);
        }
#endif

        return 0;
    }


protected:
    int offlineWrite(void)
    {
        GSLAM::Rate r(100);

        while( !_shouldStop )
        {
            while( _buffWrite.size() > 0 )
            {
                // get a new item
                SItem it;
                {
                    ScopedLock mu(_mutexWrite);

                    it = _buffWrite.front();
                    _buffWrite.pop_front();
                }

                // save to disk if necessary
                itemSave(it);
                it->buf.reset();

                // set offline flag
                it->offline = 1;
            }

            r.sleep();
        }

        return 0;
    }

    int offlineRead(void)
    {
        GSLAM::Rate r(100);

        while( !_shouldStop )
        {
            for(int i=0; i<_readAhead; i++)
            {
                SItem it;
                ScopedLock mu(_mutexQueue);

                if( i < _buff.size() )
                {
                    it = _buff[i];
                }
                else
                {
                    continue;
                }

                if( it->offline )
                {
                    itemLoad(it);
                    it->offline = 0;
                }
            }

            r.sleep();
        }

        return 0;
    }

    int itemSave(SItem& it)
    {
        char fname[2048];

        sprintf(fname, "%s_%09d", _tempPath.c_str(), it->id);
        FILE *fp = fopen(fname, "wb+");
        if( fp == NULL )
        {
            fprintf(stderr, "Can not open file for write: %s\n", fname);
            createTemps();
            return -1;
        }

        uint64_t bs = it->buf->size();
        uint8_t *pd = (uint8_t*) it->buf->data();
        fwrite(&bs,     sizeof(bs), 1, fp);
        fwrite(pd,      bs,         1, fp);

        fclose(fp);

        it->offline = 1;

        return 0;
    }

    int itemLoad(SItem& it)
    {
        char fname[2048];

        // generate temp filename
        sprintf(fname, "%s_%09d", _tempPath.c_str(), it->id);
        FILE *fp = fopen(fname, "rb");
        if( fp == NULL )
        {
            fprintf(stderr, "Can not open file for read: %s\n", fname);
            return -1;
        }

        // read data
        uint64_t bs = 0, nread;
        nread = fread(&bs, sizeof(bs), 1, fp);

        if( !it->buf ) it->buf = BuffType(new std::vector<uint8_t>(bs));
        uint8_t *pd = (uint8_t*) it->buf->data();

        nread = fread(pd, bs, 1, fp);

        fclose(fp);

        // set offline to off
        it->offline = 0;

        return 0;
    }


private:
    std::string             _tempPath;
    int                     _writeThreshold, _readAhead;
    mutable int             _uid;
    bool                    _shouldStop;
    int                     _maxQueueSize;

    std::deque<SItem>        _buff, _buffWrite;

    std::thread             _threadWrite, _threadRead;
    GSLAM::Mutex            _mutexQueue, _mutexWrite;
};


#endif // end of __OFFLINE_FIFO_H__

