#ifndef __PSTATE_H__
#define __PSTATE_H__

#include "pmap.h"
#include "pastar.h"
#include "plidar.h"

class State
{
public:
    State();
    State(RMap *map);

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

    bool findLidar(PathPoint p);
    void clear();

protected:
    RMap *m_map;

    int m_start_x, m_start_y;
    int m_end_x, m_end_y;

    int m_lox, m_loy;
    RPath m_track;
    RPath m_path;
    Rlidar m_lidar;   //所在位置的扫描结果
    Rlidar m_lidar_all; //全部扫描结果
};

#endif
