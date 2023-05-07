#ifndef __PLIDAR_H__
#define __PLIDAR_H__

#include <cstdint>
#include <vector>
#include <cmath>

#include "pmap.h"

typedef std::vector<PathPoint> Rlidar;

class Lidar // FIXME: `Lidar` is better
{
public:
    Lidar();
    Lidar(RMap *map, int32_t x, int32_t y);

    int setMap(RMap *map);
    RMap *getMap(void);

    int setPos(int x, int y);
    int getPos(int *x, int *y);

    void lidarDetect();
    Rlidar getLidares();

protected:
    RMap *m_map;
    int32_t m_lox, m_loy;
    Rlidar m_lidares;
    float m_dismax;        //最大检测距离
    float m_angap, m_disgap; //检测的角度间隔和距离间隔
};

#endif
