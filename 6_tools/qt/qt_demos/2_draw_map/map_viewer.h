/****************************************************************************
****************************************************************************/

#ifndef __MAP_VIEWER_H__
#define __MAP_VIEWER_H__

#include <QGraphicsView>
#include <QGraphicsItem>


class MapLayer;
class MapViewer;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class RMap
{
public:
    RMap()
    {
        m_mx = 0;
        m_my = 0;
        m_map = NULL;
    }

    RMap(int nx, int ny)
    {
        m_mx = nx;
        m_my = ny;
        m_map = new int[nx*ny];

        for(int i=0; i<m_mx*m_my; i++) m_map[i] = 0;
    }

    ~RMap()
    {
        if( m_map != NULL ) {
            delete [] m_map;
            m_map = NULL;
        }

        m_mx = 0;
        m_my = 0;
    }

    int getSizeX(void)
    {
        return m_mx;
    }

    int getSizeY(void)
    {
        return m_my;
    }

    int setSize(int nx, int ny)
    {
        if( m_map != NULL ) {
            delete [] m_map;
        }

        m_mx = nx;
        m_my = ny;
        m_map = new int[nx*ny];

        for(int i=0; i<nx*ny; i++) m_map[i] = 0;

        return 0;
    }

    int *getMap(void)
    {
        return m_map;
    }

    int getMapItem(int ix, int iy)
    {
        if( ix < 0 || ix > m_mx || iy < 0 || iy > m_my )
            return -1;
        else
            return m_map[iy*m_mx+ix];
    }

    int getMapItem(int i)
    {
        if( i < 0 || i > m_mx*m_my )
            return -1;
        else
            return m_map[i];
    }

    int setMapItem(int ix, int iy, int v)
    {
        if( ix < 0 || ix > m_mx || iy < 0 || iy > m_my )
            return -1;
        else
            m_map[iy*m_mx+ix] = v;

        return 0;
    }

    int setMapItem(int i, int v)
    {
        if( i < 0 || i > m_mx*m_my )
            return -1;
        else
            m_map[i] = v;

        return 0;
    }

    int clear(void)
    {
        if( m_map == NULL ) return -1;

        for(int i=0; i<m_mx*m_my; i++) m_map[i] = 0;

        return 0;
    }

protected:
    int     *m_map;
    int     m_mx, m_my;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class MapViewer : public QGraphicsView
{
    Q_OBJECT

public:
    MapViewer(QWidget *parent = 0);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void scaleView(qreal scaleFactor);
    void moveView(qreal dx, qreal dy);

    void drawBackgroud(QPainter *painter, const QRectF &rect);

protected:
    RMap        *m_map;
    MapLayer    *m_ml;

};

#endif // end of __MAP_VIEWER_H__
