#include <vector>

#include "pmap.h"
#include "pastar.h"


RMap::RMap()
{
    m_mx = 0;
    m_my = 0;
    m_map = NULL;
}

RMap::RMap(int32_t nx, int32_t ny)
{
    m_mx = nx;
    m_my = ny;
    m_map = new int8_t[nx * ny];

    for (int i = 0; i < m_mx * m_my; i++)
        m_map[i] = 0;
}

RMap::~RMap()
{
    if (m_map != NULL)
    {
        delete[] m_map;
        m_map = NULL;
    }

    m_mx = 0;
    m_my = 0;
}

int RMap::getSizeX(void)
{
    return m_mx;
}

int RMap::getSizeY(void)
{
    return m_my;
}

int RMap::setSize(int32_t nx, int32_t ny)
{
    if (m_map != NULL)
    {
        delete[] m_map;
    }

    m_mx = nx;
    m_my = ny;
    m_map = new int8_t[nx * ny];

    for (int i = 0; i < nx * ny; i++)
        m_map[i] = 0;

    return 0;
}

int8_t *RMap::getMap(void)
{
    return m_map;
}

int8_t RMap::getMapItem(int32_t ix, int32_t iy)
{
    if (ix < 0 || ix > m_mx || iy < 0 || iy > m_my)
        return -1;
    else
        return m_map[iy * m_mx + ix];
}

int8_t RMap::getMapItem(int32_t i)
{
    if (i < 0 || i > m_mx * m_my)
        return -1;
    else
        return m_map[i];
}

int RMap::setMapItem(int32_t ix, int32_t iy, int32_t v)
{
    if (ix < 0 || ix > m_mx || iy < 0 || iy > m_my)
        return -1;
    else
        m_map[iy * m_mx + ix] = v;

    return 0;
}

int RMap::setMapItem(int32_t i, int32_t v)
{
    if (i < 0 || i > m_mx * m_my)
        return -1;
    else
        m_map[i] = v;

    return 0;
}

void RMap::paintStart()
{
    m_map[m_start_x + m_start_y * m_mx] = 2;
}

void RMap::paintEnd()
{
    m_map[m_end_x + m_end_y * m_mx] = 3;
}

void RMap::paintPath(int ix, int iy)
{
    m_map[ix + iy * m_mx] = 4;
}

void RMap::paintLocat()
{
    m_map[m_lox + m_loy * m_mx] = 5;
}

void RMap::paintLidar(int ix, int iy)
{
    m_map[ix + iy * m_mx] = 2;
}

int32_t RMap::getstartX()
{
    return m_start_x;
}

int32_t RMap::getstartY()
{
    return m_start_y;
}

int32_t RMap::getendX()
{
    return m_end_x;
}

int32_t RMap::getendY()
{
    return m_end_y;
}

int32_t RMap::getlocX()
{
    return m_lox;
}

int32_t RMap::getlocY()
{
    return m_loy;
}

int RMap::clear(void)
{
    if (m_map == NULL)
        return -1;

    for (int i = 0; i < m_mx * m_my; i++)
        m_map[i] = 0;

    return 0;
}

int RMap::loadMap(const char *fname)
{
    FILE *fp = NULL;
    int res, ret = -1;

    uint32_t f_magic;

    // open file
    fp = fopen(fname, "rb");
    if (fp == NULL)
    {
        printf("ERR: failed to open file %s!\n", fname);
        return -1;
    }

    // check file magic number
    res = fread(&f_magic, sizeof(uint32_t), 1, fp);
    if (f_magic != 0x15432345)
    {
        printf("ERR: input file format is not correct! %s\n", fname);
        goto RMAP_LOAD_RET;
    }

    // read map nx, ny
    res = fread(&m_mx, sizeof(int32_t), 1, fp);
    res = fread(&m_my, sizeof(int32_t), 1, fp);

    // read map
    if (m_map != NULL)
        delete[] m_map;
    m_map = new int8_t[m_mx * m_my];
    res = fread(m_map, sizeof(int8_t), m_mx * m_my, fp);

    // read start,end point
    res = fread(&m_start_x, sizeof(int32_t), 1, fp);
    res = fread(&m_start_y, sizeof(int32_t), 1, fp);
    res = fread(&m_end_x, sizeof(int32_t), 1, fp);
    res = fread(&m_end_y, sizeof(int32_t), 1, fp);

    m_lox = m_start_x;
    m_loy = m_start_y;

    // return
    ret = 0;

RMAP_LOAD_RET:
    fclose(fp);

    return ret;
}
