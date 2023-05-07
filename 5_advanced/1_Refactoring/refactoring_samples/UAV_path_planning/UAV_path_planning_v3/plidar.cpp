#include "plidar.h"

Lidar::Lidar()
{
    m_map = NULL;

    m_lox = 0;
    m_loy = 0;
}

Lidar::Lidar(RMap *map, int32_t x, int32_t y)
{
    m_dismax = 25.0;
    m_angap = 0.5;
    m_disgap = 0.5;
    m_lox = x;
    m_loy = y;
    m_map = map;
}

int Lidar::setMap(RMap *map)
{
    m_map = map;

    return 0;
}

RMap *Lidar::getMap(void)
{
    return m_map;
}

int Lidar::setPos(int x, int y)
{
    m_lox = x;
    m_loy = y;

    return 0;
}

int Lidar::getPos(int *x, int *y)
{
    *x = m_lox;
    *y = m_loy;

    return 0;
}

void Lidar::lidarDetect()
{
    float theta, dis;
    float dx, dy;
    int x, y;
    int n = 360 / m_angap; //射线条数
    for (int i = 0; i < n; i++)
    {
        theta = i * m_angap * M_PI / 180.0;                  //射线角度
        for (dis = 0.5; dis <= m_dismax; dis = dis + m_disgap) //某一角度的射线延长至最大侦察范围
        {
            dx = cos(theta) * dis;
            dy = sin(theta) * dis;
            x = m_lox + int(dx);
            y = m_loy + int(dy);
            if (x < 0 || x > m_map->getSizeX() || y < 0 || y > m_map->getSizeY())
                break;
            if (m_map->getMapItem(x, y) == 1)
            {
                PathPoint p;
                p.x = x;
                p.y = y;
                m_lidares.push_back(p);
            }
        }
    }
}

Rlidar Lidar::getLidares()
{
    return m_lidares;
}
