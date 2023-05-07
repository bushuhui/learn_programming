#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "Status.h"

Status::Status()
{
    m_map = NULL;

    m_startX = -1;
    m_startY = -1;
    m_endX = -1;
    m_endY = -1;

    lo_x = -1;
    lo_y = -1;
}

Status::Status(RMap *map)
{
    m_map = map;

    m_startX = map->getstartX();
    m_startY = map->getstartY();
    m_endX = map->getendX();
    m_endY = map->getendY();
    lo_x = map->getlocX();
    lo_y = map->getlocY();
}

int Status::setMap(RMap *map)
{
    m_map = map;

    m_startX = map->getstartX();
    m_startY = map->getstartY();
    m_endX = map->getendX();
    m_endY = map->getendY();

    return 0;
}

int Status::getMap(RMap *map)
{
    map = m_map;

    return 0;
}

int Status::setStart(int x, int y)
{
    m_startX = x;
    m_startY = y;

    return 0;
}

int Status::getStart(int *px, int *py)
{
    *px = m_startX;
    *py = m_startY;

    return 0;
}

int Status::setEnd(int x, int y)
{
    m_endX = x;
    m_endY = y;

    return 0;
}

int Status::getEnd(int *px, int *py)
{
    *px = m_endX;
    *py = m_endY;

    return 0;
}

void Status::clear()
{
    m_lidar.clear();
    lidar_all.clear();
    m_path.clear();
    m_track.clear();
    lo_x = m_startX;
    lo_y = m_startY;
}

void Status::setLoc(int x, int y)
{
    lo_x = x;
    lo_y = y;
}

int Status::getLoc(int *px, int *py)
{
    *px = lo_x;
    *py = lo_y;

    return 0;
}

void Status::runPath()
{
    vector<vector<int>> arr;
    for (int i = 0; i < m_map->getSizeY(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < m_map->getSizeX(); j++)
        {
            point p;
            p.x = i;
            p.y = j;
            if (m_map->getMapItem(i, j) == 1 && findLidar(p) == true)
            {
                temp.push_back(1);
            }
            else
                temp.push_back(0);
            // m_map->getMapItem(i, j)
        }
        arr.push_back(temp);
        temp.clear();
    }
    Point s(lo_y, lo_x);
    Point e(m_endY, m_endX);
    Astar as;
    vector<Point> result = as.AstarRes(arr, s, e);
    vector<point> path;
    for (int i = 0; i < result.size(); i++)
    {
        point p;
        p.x = result[i].y;
        p.y = result[i].x;
        path.push_back(p);
    }
    m_path = path;
}

void Status::runLidar()
{
    lidar li(m_map, lo_x, lo_y);
    li.lidarDetect();
    m_lidar = li.getlidarRes(); //实时更新所在位置的探测结果

    for (int i = 0; i < m_lidar.size(); i++)
    {
        point p = m_lidar[i];
        if (findLidar(p) == false)
            lidar_all.push_back(p);
    } //实时更新所有探测结果
}

RPath Status::getPath()
{
    return m_path;
}

RPath Status::getTrack()
{
    point p;
    p.x = lo_x;
    p.y = lo_y;
    m_track.push_back(p);
    return m_track; //记录行进踪迹
}

Rlidar Status::getLidar()
{
    return m_lidar;
}

bool Status::findLidar(point p)
{
    for (int i = 0; i < lidar_all.size(); i++)
    {
        if (p.x == lidar_all[i].x && p.y == lidar_all[i].y)
            return true;
    }
    return false;
}