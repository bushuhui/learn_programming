#include "lidar.h"

lidar::lidar()
{
    m_map = NULL;

    lo_x = 0;
    lo_y = 0;
}

lidar::lidar(RMap *map, int32_t x, int32_t y)
{
    dismax = 25.0;
    angap = 0.5;
    disgap = 0.5;
    lo_x = x;
    lo_y = y;
    m_map = map;
}

int lidar::setMap(RMap *map)
{
    m_map = map;

    return 0;
}

RMap *lidar::getMap(void)
{
    return m_map;
}

int lidar::setPos(int x, int y)
{
    lo_x = x;
    lo_y = y;

    return 0;
}

int lidar::getPos(int *x, int *y)
{
    *x = lo_x;
    *y = lo_y;

    return 0;
}

void lidar::lidarDetect()
{
    float theta, dis;
    float dx, dy;
    int x, y;
    int n = 360 / angap; //射线条数
    for (int i = 0; i < n; i++)
    {
        theta = i * angap * M_PI / 180.0;                  //射线角度
        for (dis = 0.5; dis <= dismax; dis = dis + disgap) //某一角度的射线延长至最大侦察范围
        {
            dx = cos(theta) * dis;
            dy = sin(theta) * dis;
            x = lo_x + int(dx);
            y = lo_y + int(dy);
            if (x < 0 || x > m_map->getSizeX() || y < 0 || y > m_map->getSizeY())
                break;
            if (m_map->getMapItem(x, y) == 1)
            {
                point p;
                p.x = x;
                p.y = y;
                m_lidarRes.push_back(p);
            }
        }
    }
}

Rlidar lidar::getlidarRes()
{
    return m_lidarRes;
}
