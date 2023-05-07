#ifndef __STATUS_H__
#define __STATUS_H__

#include "RMap.h"
#include "Astar.h"
#include "lidar.h"

// FIXME: this class name is not clear
class Status
{
public:
    Status();
    Status(RMap *map);

    int setMap(RMap *map);
    int getMap(RMap *map);

    int setStart(int x, int y);
    int getStart(int *px, int *py);
    int setEnd(int x, int y);
    int getEnd(int *px, int *py);

    void setLoc(int x, int y);
    int getLoc(int *px, int *py);

    void runPath();  // run Astar to get path
    void runLidar(); // run lidar to detect

    RPath getPath();
    RPath getTrack();
    Rlidar getLidar();

    bool findLidar(point p);
    void clear();

protected:
    RMap *m_map;

    int m_startX, m_startY;
    int m_endX, m_endY;

    int lo_x, lo_y;
    RPath m_track;
    RPath m_path;
    Rlidar m_lidar;   //所在位置的扫描结果
    Rlidar lidar_all; //全部扫描结果
};

#endif
