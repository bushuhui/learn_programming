/****************************************************************************
****************************************************************************/

#ifndef __MAP_VIEWER_H__
#define __MAP_VIEWER_H__

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <cstdint>
#include <fstream>

#include <RMap.h>
#include <Status.h>

class MapLayer;
class MapViewer;

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
    RMap *m_map;
    MapLayer *m_ml;
    Status *m_status;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MapLayer : public QGraphicsItem
{
public:
    MapLayer(MapViewer *mv, RMap *map, Status *status);

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
    Status *m_status;
};


#endif // end of __MAP_VIEWER_H__
