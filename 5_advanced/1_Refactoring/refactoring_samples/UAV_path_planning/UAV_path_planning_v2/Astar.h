#pragma once

#include <assert.h>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


struct Point
{
    int32_t x; // 宽
    int32_t y; // 高
    Point(int32_t tx = 0, int32_t ty = 0) : x(tx), y(ty) {}

    // 两个坐标距离：横坐标距离 + 纵坐标距离
    int operator-(const Point &p)
    {
        return abs(x - p.x) + abs(y - p.y);
    }

    bool operator==(const Point &p)
    {
        return x == p.x && y == p.y;
    }
};

struct PointV : public Point
{
    int value; // 0 :无障碍; 1:有障碍
    PointV(int nx = 0, int ny = 0, int v = 0) : Point(nx, ny), value(v) {}
};

struct PointAStart : public Point
{
    int f, g, h;
    bool visited; // 是否被访问过，0：未被访问，1已经被访问
    Point parentNode;

    PointAStart(int tf = 0, int tg = 0, int th = 0, int tx = 0, int ny = 0) : Point(tx, ny), f(tf), g(tg), h(th), visited(false), parentNode(){};
    bool operator<(const PointAStart &t) { return f < t.f; }
    void SetFGH(int tf, int tg, int th)
    {
        f = tf;
        g = tg, h = th;
    }
};

struct comp //重写仿函数
{
    bool operator()(PointAStart *a, PointAStart *b)
    {
        return a->f > b->f; //小顶堆
    }
};

// A* 算法
class Astar
{
public:
    vector<Point> AstarRes(const vector<vector<int>> &arr, Point s, Point e);
};
