#include <assert.h>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <algorithm>
#include "Astar.h"

using namespace std;

#define GET_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// A* 算法
vector<Point> Astar::AstarRes(const vector<vector<int>> &arr, Point s, Point e)
{

    // arr 是一个二维数组
    // s 起点; e 终点

    if (arr.empty() || s == e)
        return {};

    int lenY = (int)arr.size() - 1;    // 高
    int lenX = (int)arr[0].size() - 1; // 宽

    if (s.x > lenX || s.y > lenY || e.x > lenX || e.y > lenY)
        return {};

    if (arr[s.y][s.x] != 0 || arr[e.y][e.x] != 0)
        return {};

    for (int i = 0; i < lenY; ++i)
        assert(lenX == (int)arr[i].size() - 1);

    vector<vector<PointAStart>> pArr(lenY + 1, vector<PointAStart>(lenX + 1)); // 父结点
    priority_queue<PointAStart *, vector<PointAStart *>, comp> openList;       // 改用优先队列

    int g = 0, h = (s - e) * 10, f = g + h;
    PointAStart pt(f, g, h, s.x, s.y);
    pt.visited = true;
    pArr[s.y][s.x] = pt;
    openList.push(&pArr[s.y][s.x]);

    bool seek = true;
    const int dirs[4][3] = {{0, 1, 10}, {1, 0, 10}, {0, -1, 10}, {-1, 0, 10}}; // 4个移动方向（右，右上，上，左上，左，左下，下，右下）
    while (seek && !openList.empty())
    {
        PointAStart &p = *openList.top();
        openList.pop();
        p.visited = true;

        for (int i = 0; i < GET_ARRAY_LEN(dirs) && seek; ++i)
        {
            Point t(p.x + dirs[i][1], p.y + dirs[i][0]);
            // t 需要未被访问
            if (t.x < 0 || t.x > lenX || t.y < 0 || t.y > lenY || arr[t.y][t.x] == 1 || pArr[t.y][t.x].visited)
                continue;

            // 找父节点
            g = p.g + dirs[i][2];
            h = (t - e) * 10;
            f = g + h;
            int minf = f;
            PointAStart newPoint(f, g, h, t.x, t.y);
            newPoint.visited = 1;
            newPoint.parentNode.x = p.x;
            newPoint.parentNode.y = p.y;
            for (int j = 0; j < GET_ARRAY_LEN(dirs); ++j)
            {
                Point pp(t.x + dirs[j][1], t.y + dirs[j][0]); //父节点Parent Point
                // 父节点pp, 在需要已经被访问
                if (pp.x < 0 || pp.x > lenX || pp.y < 0 || pp.y > lenY || arr[pp.y][pp.x] == 1 || !pArr[pp.y][pp.x].visited)
                    continue;

                g = pArr[pp.y][pp.x].g + dirs[j][2];
                f = g + h;
                if (f <= minf)
                {
                    minf = f;
                    f = g + h;

                    newPoint.SetFGH(f, g, h);
                    newPoint.parentNode = pp;
                }
            }

            pArr[t.y][t.x] = newPoint;
            openList.push(&pArr[t.y][t.x]);

            if (t == e)
                seek = false;
        }
    }

    if (!pArr[e.y][e.x].visited)
    {
        cout << "无法到达" << endl;
        return {};
    }
    else
    {
        vector<Point> path;
        path.push_back(e);
        Point p = pArr[e.y][e.x].parentNode;
        while (true)
        {
            if (!pArr[p.y][p.x].visited)
            {
                cout << "无法到达" << endl;
                return {};
            }

            path.push_back(p);
            if (p == s)
                break;

            p = pArr[p.y][p.x].parentNode;
        }

        reverse(path.begin(), path.end());

        return path;
    }
};
