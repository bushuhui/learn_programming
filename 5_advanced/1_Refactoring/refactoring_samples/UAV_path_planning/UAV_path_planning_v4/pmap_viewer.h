/****************************************************************************
****************************************************************************/

#ifndef __PMAP_VIEWER_H__
#define __PMAP_VIEWER_H__

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

#include <QGraphicsView>
#include <QGraphicsItem>

#include <cstdint>
#include <fstream>
#include <QThread>
#include <QFileDialog>
#include <QByteArray>
#include <math.h>
#include <vector>

#include "pmap.h"
#include "pstate.h"
#include "psimulation.h"

class MapLayer;
class MapViewer;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class MapViewer : public QGraphicsView
{
    Q_OBJECT

public:
    MapViewer(QWidget *parent = 0);
    int pathswitch;
    int lidarswitch;
    int trackswitch;

    int moveswitch;
    int showswitch;
    int clearswitch;
    int menuswitch;

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
    RMap *m_map;
    MapLayer *m_ml;
    State *m_state;
    Simulation*  m_simulation;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MapLayer : public QGraphicsItem
{
public:
    MapLayer(MapViewer *mv, RMap *map, State *status,Simulation *s);
    
    int setMap(RMap *m);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    RMap *m_map;
    MapViewer *m_mv;
    State *m_state;
    Simulation *m_simulation;
};


#endif // end of __MAP_VIEWER_H__
