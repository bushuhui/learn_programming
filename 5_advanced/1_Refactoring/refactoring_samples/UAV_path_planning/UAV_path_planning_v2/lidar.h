#ifndef __LIDAR_H__
#define __LIDAR_H__

#include <cstdint>
#include <vector>
#include <cmath>

#include "RMap.h"

typedef std::vector<point> Rlidar;

class lidar
{
public:
    lidar();
    lidar(RMap *map, int32_t x, int32_t y);

    int setMap(RMap *map);
    RMap *getMap(void);

    int setPos(int x, int y);
    int getPos(int *x, int *y);

    void lidarDetect();
    Rlidar getlidarRes();

protected:
    RMap *m_map;
    int32_t lo_x, lo_y;
    Rlidar m_lidarRes;
    float dismax;        //最大检测距离
    float angap, disgap; //检测的角度间隔和距离间隔
};

#endif
