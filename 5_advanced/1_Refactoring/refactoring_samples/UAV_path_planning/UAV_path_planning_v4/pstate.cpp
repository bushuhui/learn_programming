#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "pstate.h"

State::State()
{
    m_map = NULL;

    m_start_x = -1;
    m_start_y = -1;
    m_end_x = -1;
    m_end_y = -1;

    m_lox = -1;
    m_loy = -1;
}

State::State(RMap *map)
{
    m_map = map;

    m_start_x = map->getstartX();
    m_start_y = map->getstartY();
    m_end_x = map->getendX();
    m_end_y = map->getendY();
    m_lox = map->getlocX();
    m_loy = map->getlocY();
}

int State::setMap(RMap *map)
{
    m_map = map;

    m_start_x = map->getstartX();
    m_start_y = map->getstartY();
    m_end_x = map->getendX();
    m_end_y = map->getendY();

    return 0;
}

int State::getMap(RMap *map)
{
    map = m_map;

    return 0;
}

int State::setStart(int x, int y)
{
    m_start_x = x;
    m_start_y = y;

    return 0;
}

int State::getStart(int *px, int *py)
{
    *px = m_start_x;
    *py = m_start_y;

    return 0;
}

int State::setEnd(int x, int y)
{
    m_end_x = x;
    m_end_y = y;

    return 0;
}

int State::getEnd(int *px, int *py)
{
    *px = m_end_x;
    *py = m_end_y;

    return 0;
}

void State::clear()
{
    m_lidar.clear();
    m_lidar_all.clear();
    m_path.clear();
    m_track.clear();
    m_lox = m_start_x;
    m_loy = m_start_y;
}

void State::setLoc(int x, int y)
{
    m_lox = x;
    m_loy = y;
}

int State::getLoc(int *px, int *py)
{
    *px = m_lox;
    *py = m_loy;

    return 0;
}

void State::runPath()
{
    vector<vector<int>> arr;
    for (int i = 0; i < m_map->getSizeY(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < m_map->getSizeX(); j++)
        {
            PathPoint p;
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
    Point s(m_loy, m_lox);
    Point e(m_end_y, m_end_x);
    Astar as;
    vector<Point> result = as.AstarRes(arr, s, e);
    vector<PathPoint> path;
    for (int i = 0; i < result.size(); i++)
    {
        PathPoint p;
        p.x = result[i].y;
        p.y = result[i].x;
        path.push_back(p);
    }
    m_path = path;
}

void State::runLidar()
{
    Lidar li(m_map, m_lox, m_loy);
    li.lidarDetect();
    m_lidar = li.getLidares(); //实时更新所在位置的探测结果

    for (int i = 0; i < m_lidar.size(); i++)
    {
        PathPoint p = m_lidar[i];
        if (findLidar(p) == false)
            m_lidar_all.push_back(p);
    } //实时更新所有探测结果
}

RPath State::getPath()
{
    return m_path;
}

RPath State::getTrack()
{
    PathPoint p;
    p.x = m_lox;
    p.y = m_loy;
    m_track.push_back(p);
    return m_track; //记录行进踪迹
}

Rlidar State::getLidar()
{
    return m_lidar;
}

bool State::findLidar(PathPoint p)
{
    for (int i = 0; i < m_lidar_all.size(); i++)
    {
        if (p.x == m_lidar_all[i].x && p.y == m_lidar_all[i].y)
            return true;
    }
    return false;
}