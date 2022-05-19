#ifndef __COMM_H__
#define __COMM_H__

#include "GSLAM.h"
#include "Svar.h"

#include <vector>

namespace GSLAM {

/**
 * @brief The Communication Base class
 *
 */
class CommunicationBase : public GObject
{
public:
    CommunicationBase() {}
    virtual ~CommunicationBase() {}

    virtual void  call(const std::string& command,void* arg=NULL){}
    virtual std::string type()const{return "CommunicationBase";}

    virtual int openDevice(Svar& conf);
    virtual int read(std::vector<unsigned char>& buf, int buf_len);
    virtual int write(std::vector<unsigned char>& buf);
};


/**
 * @brief The UDP Communication class
 *
 */
class CommunicationUDP : public CommunicationBase
{
    CommunicationUDP() {}
    virtual ~CommunicationUDP() {}

    virtual void  call(const std::string& command,void* arg=NULL){}
    virtual std::string type()const{return "CommunicationUDP";}

    virtual int openDevice(Svar& conf);
    virtual int read(std::vector<unsigned char>& buf, int buf_len);
    virtual int write(std::vector<unsigned char>& buf);
};

} // end of namespace GSLAM

#endif // end of __COMM_H__

