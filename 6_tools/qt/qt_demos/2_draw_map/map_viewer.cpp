/****************************************************************************
****************************************************************************/

#include <stdio.h>
#include <math.h>

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

#include "map_viewer.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MapLayer : public QGraphicsItem
{
public:
    MapLayer(MapViewer *mv, RMap *map);

    int setMap(RMap *m);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    RMap        *m_map;
    MapViewer   *m_mv;
};


MapLayer::MapLayer(MapViewer *mv, RMap *map)
{
    m_map = map;
    m_mv = mv;

    //setFlag(ItemIsMovable);
    //setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

int MapLayer::setMap(RMap *m)
{
    m_map = m;
    return 0;
}

QRectF MapLayer::boundingRect() const
{
    qreal adjust = 2;

    return QRectF(0-adjust, 0-adjust, m_map->getSizeX()+adjust, m_map->getSizeY()+adjust);
}

QPainterPath MapLayer::shape() const
{
    QPainterPath path;

    path.addRect(0, 0, m_map->getSizeX(), m_map->getSizeY());
    return path;
}

void MapLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int     nx, ny;
    int     i, j, ix, iy;
    qreal   dx, dy, x1, y1, x2, y2;
    int     v;

    nx = m_map->getSizeX();
    ny = m_map->getSizeY();

    dx = 1;
    dy = 1;

    // draw grid
    x1 = 0;
    y1 = 0;

    y2 = ny;
    painter->setPen(Qt::gray);
    for(i=0; i<nx+1; i++) {
        x2 = x1 + i*dx;
        painter->drawLine(x2, y1, x2, y2);
    }

    x2 = nx;
    for(i=0; i<ny+1; i++) {
        y2 = y1 + i*dy;
        painter->drawLine(x1, y2, x2, y2);
    }

    // draw cells
    for(i=0; i<nx*ny; i++) {
        v = m_map->getMapItem(i);

        if( v == 0 ) continue;

        ix = i % nx;
        iy = i / ny;

        x2 = x1 + ix*dx;
        y2 = y1 + iy*dy;

        if( v == 1 ) painter->fillRect(x2, y2, dx, dy, Qt::black);
    }
}


QVariant MapLayer::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //printf("itemChange = %d\n", change);
    //this->update();
    return QGraphicsItem::itemChange(change, value);
}

void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt;
    float   cx, cy;
    int     ix, iy, idx;
    int     nx, ny;

    pt = this->pos();
    cx = event->scenePos().x() - pt.x();
    cy = event->scenePos().y() - pt.y();
    //printf("mousePressEvent = (%f %f)\n", cx, cy);

    nx = m_map->getSizeX();
    ny = m_map->getSizeY();
    ix = (int)( cx );
    iy = (int)( cy );
    idx = iy*nx + ix;

    if( m_map->getMapItem(idx) == 0 )
        m_map->setMapItem(idx, 1);
    else
        m_map->setMapItem(idx, 0);

    update();
}

void MapLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt;
    float   cx, cy;

    pt = this->pos();
    cx = event->scenePos().x() - pt.x();
    cy = event->scenePos().y() - pt.y();

    //printf("mouseReleaseEvent = (%f %f)\n", cx, cy);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MapViewer::MapViewer(QWidget *parent)
    : QGraphicsView(parent)
{
    // init map data
    m_map = new RMap(100, 100);

    qreal off = 5;
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0-off, 0-off, m_map->getSizeX()+off*2, m_map->getSizeY()+off*2);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);

    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(5), qreal(5));

    setMinimumSize(600, 600);
    setWindowTitle(tr("Map viewer"));

    m_ml = new MapLayer(this, m_map);
    m_ml->setPos(0, 0);
    scene->addItem(m_ml);
}


void MapViewer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        //this->moveView(0, -1);
        m_ml->moveBy(0, -10);
        //m_ml->update();
        break;
    case Qt::Key_Down:
        m_ml->moveBy(0, 10);
        break;
    case Qt::Key_Left:
        m_ml->moveBy(-10, 0);
        break;
    case Qt::Key_Right:
        m_ml->moveBy(10, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void MapViewer::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 400.0));
}

void MapViewer::drawBackgroud(QPainter *painter, const QRectF &rect)
{

}


void MapViewer::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.2 || factor > 150)
        return;

    scale(scaleFactor, scaleFactor);
}

void MapViewer::moveView(qreal dx, qreal dy)
{
    qreal   w, h;
    qreal   mx, my;

    qreal factor = transform().scale(1, 1).mapRect(QRectF(0, 0, 1, 1)).width();
    printf("factor = %f\n", factor);


    QRectF sceneRect = this->sceneRect();


    w = sceneRect.width();
    h = sceneRect.height();

    mx = dx*w/10.0;
    my = dy*h/10.0;

    sceneRect.translate(mx, my);
    setSceneRect(sceneRect);

    printf("x, y   = %f %f\n", sceneRect.left(), sceneRect.top());
    printf("mx, my = %f %f\n\n", mx, my);

    this->update();
}


void MapViewer::zoomIn()
{
    scaleView(qreal(1.2));
}

void MapViewer::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
