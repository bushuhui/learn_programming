#ifndef __PMAP_H__
#define __PMAP_H__

#include <stdio.h>
#include <stdint.h>
#include <cstdint>
#include <fstream>
#include <vector>

struct PathPoint
{
    int x;
    int y; // map position
};

typedef std::vector<PathPoint> RPath;

class RMap
{
public:
    RMap();
    RMap(int32_t nx, int32_t ny);
    ~RMap();

    int getSizeX(void);
    int getSizeY(void);
    int8_t *getMap(void);
    int8_t getMapItem(int32_t ix, int32_t iy);
    int8_t getMapItem(int32_t i);

    int setSize(int32_t nx, int32_t ny);
    int setMapItem(int32_t ix, int32_t iy, int32_t v);
    int setMapItem(int32_t i, int32_t v);

    void paintStart();
    void paintEnd();
    void paintPath(int ix, int iy);
    void paintLocat();
    void paintLidar(int ix, int iy);

    int32_t getstartX();
    int32_t getstartY();
    int32_t getendX();
    int32_t getendY();
    int32_t getlocX();
    int32_t getlocY();

    int loadMap(const char *fname);
    int clear(void);

protected:
    int8_t *m_map;
    int32_t m_mx, m_my;
    int32_t m_start_x, m_start_y;
    int32_t m_end_x, m_end_y;
    int32_t m_lox, m_loy;
};
#endif
