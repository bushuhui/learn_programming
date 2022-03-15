#ifndef __DATALINK_PROTOCOL_H__
#define __DATALINK_PROTOCOL_H__

#include "GSLAM.h"
#include "uav.h"

namespace GSLAM
{

class Datalink_Protocol : public GObject
{
public:
    Datalink_Protocol() {}
    virtual ~Datalink_Protocol() {}


    /**
     * @brief parse data buffer to generate UAV data package
     * @param buf - buffer pointer
     * @param buflen - buffer length
     * @return 0 - parse success, other - failed
     */
    virtual int parse_fromBuf(UavData& uav, uint8_t *buf, int buflen) = 0;


    /**
     * @brief parse data buffer to generate UAV data package
     * @param buf - buffer object
     * @return 0 - parse success, other - failed
     */
    virtual int parse_fromBuf(UavData& uav, std::vector<unsigned char>& buf) = 0;


    /**
     * @brief generate given UAV command's data buffer
     * @param cmd - command
     * @param buf - generated data buffer
     * @param parm - other parameters
     * @return 0 - success, other - failed
     */
    virtual int package_toBuf(UavData& uav,
                              const std::string& cmd, std::vector<unsigned char>& buf,
                              Svar* parm=NULL) = 0;

};


}


#endif // end of __DATALINK_PROTOCOL_H__


