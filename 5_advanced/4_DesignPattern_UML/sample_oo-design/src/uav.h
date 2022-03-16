#ifndef __UAV_H__
#define __UAV_H__

#include <stdint.h>

#include "GSLAM.h"
#include "Svar.h"

namespace GSLAM
{


class UavBaseData : public GObject
{
public:
    uint8_t             ID, compID;             ///< mavlink ID number
    uint8_t             gcsID, gcsCompID;       ///< GCS ID & Component ID

    uint8_t             uavType;                ///< UAV type

    // navigation data
    uint64_t            gpsTime;                ///< GPS time
    double              lat, lon, alt;          ///< GPS raw position
    double              HDOP_h, HDOP_v;         ///< HDOP
    double              gpsGroundSpeed;         ///< ground speed
    int                 gpsFixType;             ///< GPS fix type
    int                 nSat;                   ///< visable satellite

    double              gpLat, gpLon;           ///< fused position
    double              gpAlt, gpH;             ///< altitude / height
    double              gpVx, gpVy, gpVz;       ///< speed
    double              gpHeading;              ///< heading

    float               roll, pitch, yaw;       ///< attitude
    float               rollSpd,
                        pitchSpd,
                        yawSpd;

public:
    UavBaseData() {}
    virtual ~UavBaseData() {}

    virtual void  call(const std::string& command,void* arg=NULL){}
    virtual std::string type()const {return "UavBaseData";}

    /**
     * @brief Get all data in svar type
     * @return
     */
    virtual Svar& getData(void) = 0;

    /**
     * @brief Set data by svar type
     * @param dat - Svar data package
     * @return 0 - success, other - failed
     */
    virtual int setData(Svar& dat) = 0;
};


class UavData : public UavBaseData
{
public:
    UavData() {}
    virtual ~UavData() {}

    virtual void  call(const std::string& command,void* arg=NULL){}
    virtual std::string type()const {return "UavData";}

    virtual Svar& getData(void) {}
    virtual int setData(Svar& dat) {}


private:
    Svar uavExtData;
};


} // end of namespace GSLAM

#endif // end of __UAV_H__

