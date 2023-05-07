/****************************************************************************
****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <vector>

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

#include "map_viewer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MapLayer::MapLayer(MapViewer *mv, RMap *map, Status *status) //初始化maplayer
{
    m_map = map;
    m_mv = mv;
    m_status = status;
    // setFlag(ItemIsMovable);
    // setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

int MapLayer::setMap(RMap *m) //设置给定的map
{
    m_map = m;
    return 0;
}

QRectF MapLayer::boundingRect() const //矩形窗口
{
    qreal adjust = 2;

    return QRectF(0 - adjust, 0 - adjust, m_map->getSizeX() + adjust, m_map->getSizeY() + adjust);
}

QPainterPath MapLayer::shape() const //图形构造块
{
    QPainterPath path;

    path.addRect(0, 0, m_map->getSizeX(), m_map->getSizeY());
    return path;
}

void MapLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //绘制网格
{
    int nx, ny;
    int i, j, ix, iy;
    qreal dx, dy, x1, y1, x2, y2;
    int v;

    nx = m_map->getSizeX();
    ny = m_map->getSizeY();

    dx = 1;
    dy = 1;

    // draw grid
    x1 = 0;
    y1 = 0;

    y2 = ny;
    painter->setPen(Qt::gray);
    for (i = 0; i < nx + 1; i++)
    {
        x2 = x1 + i * dx;
        painter->drawLine(x2, y1, x2, y2);
    }

    x2 = nx;
    for (i = 0; i < ny + 1; i++)
    {
        y2 = y1 + i * dy;
        painter->drawLine(x1, y2, x2, y2);
    }

    // draw cells
    for (i = 0; i < nx * ny; i++)
    {
        v = m_map->getMapItem(i);

        if (v == 0)
            continue;

        ix = i % nx;
        iy = i / ny;

        x2 = x1 + ix * dx;
        y2 = y1 + iy * dy;

        if (v == 1)
            painter->fillRect(x2, y2, dx, dy, Qt::black); //障碍物
    }

    // draw start

    ix = m_map->getstartX();
    iy = m_map->getstartY();
    if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
    {
        x2 = x1 + ix * dx;
        y2 = y1 + iy * dy;

        painter->fillRect(x2, y2, dx, dy, Qt::red);
    }

    // draw end

    ix = m_map->getendX();
    iy = m_map->getendY();
    if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
    {
        x2 = x1 + ix * dx;
        y2 = y1 + iy * dy;

        painter->fillRect(x2, y2, dx, dy, Qt::blue);
    }

    // draw path

    RPath pathres;

    pathres = m_status->getPath();

    for (int i = 1; i < pathres.size() - 1; i++)
    {
        ix = pathres[i].x;
        iy = pathres[i].y;
        if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
        {
            x2 = x1 + ix * dx;
            y2 = y1 + iy * dy;
            painter->fillRect(x2, y2, dx, dy, Qt::green);
        }
    }

    // draw lidar_detect area

    Rlidar lidarres;

    lidarres = m_status->getLidar();

    for (int i = 0; i < lidarres.size(); i++)
    {
        ix = lidarres[i].x;
        iy = lidarres[i].y;
        if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
        {
            x2 = x1 + ix * dx;
            y2 = y1 + iy * dy;
            painter->fillRect(x2, y2, dx, dy, Qt::red);
        }
    }

    // draw track

    RPath track;
    track = m_status->getTrack();
    for (int i = 0; i < track.size(); i++)
    {
        ix = track[i].x;
        iy = track[i].y;
        if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
        {
            x2 = x1 + ix * dx;
            y2 = y1 + iy * dy;
            painter->fillRect(x2, y2, dx, dy, QColor(0, 255, 255));
        }
    }

    // draw current position

    m_status->getLoc(&ix, &iy);

    if (ix >= 0 && ix < nx && iy >= 0 && iy < ny)
    {
        x2 = x1 + ix * dx;
        y2 = y1 + iy * dy;

        painter->setPen(QPen(QColor(255, 0, 255), 0.1, Qt::NoPen));
        painter->setBrush(QColor(255, 0, 255));
        painter->fillRect(x2, y2, dx, dy, QColor(255, 0, 255));
    }
}

QVariant MapLayer::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // printf("itemChange = %d\n", change);
    // this->update();
    return QGraphicsItem::itemChange(change, value);
}

void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt;
    float cx, cy;
    int ix, iy, idx;
    int nx, ny;

    pt = this->pos();
    cx = event->scenePos().x() - pt.x();
    cy = event->scenePos().y() - pt.y();
    // printf("mousePressEvent = (%f %f)\n", cx, cy);

    nx = m_map->getSizeX();
    ny = m_map->getSizeY();
    ix = (int)(cx);
    iy = (int)(cy);
    idx = iy * nx + ix;

    if (m_map->getMapItem(idx) == 0)
        m_map->setMapItem(idx, 1);
    else
        m_map->setMapItem(idx, 0);

    update();
}

void MapLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt;
    float cx, cy;

    pt = this->pos();
    cx = event->scenePos().x() - pt.x();
    cy = event->scenePos().y() - pt.y();

    // printf("mouseReleaseEvent = (%f %f)\n", cx, cy);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MapViewer::MapViewer(QWidget *parent)
    : QGraphicsView(parent)
{
    // init map data
    m_map = new RMap(100, 100);
    m_map->loadMap("test_1.map"); //得到地图数据 // FIXME: if can not load the map file, then program crashed
                                               //        add a open file dialog to select a map file

    m_status = new Status(m_map);
    m_status->runPath();
    m_status->runLidar(); //得到状态数据

    qreal off = 5;
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0 - off, 0 - off, m_map->getSizeX() + off * 2, m_map->getSizeY() + off * 2);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);

    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(5), qreal(5));

    setMinimumSize(600, 600);
    setWindowTitle(tr("UAV Path Planning"));

    m_ml = new MapLayer(this, m_map, m_status); //状态加入
    m_ml->setPos(0, 0);
    scene->addItem(m_ml);
}

void MapViewer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_M: //按M进行点的移动
    {
        // FIXME: this path need improve, do not do all thing in this path, create a new Simulation class do planning, scan, move, update ....
        RPath pathres1, pathres2;
        pathres1 = m_status->getPath(); //初始未探测到障碍物的路径
        int n1 = pathres1.size();
        for (int i = 1; i < pathres1.size(); i++)
        {
            m_status->setLoc(pathres1[i].x, pathres1[i].y);
            m_status->runLidar();
            m_status->runPath();
            pathres2 = m_status->getPath();
            int n2 = pathres2.size();
            if (pathres2[n2 - 2].x != pathres1[n1 - 2].x)
                break; //探测到所有障碍物后的可行路径
            else
            {
                m_ml->update();
                qApp->processEvents();
            }
        }
        for (int i = 1; i < pathres2.size(); i++)
        {
            m_status->setLoc(pathres2[i].x, pathres2[i].y);
            m_status->runLidar();
            m_ml->update();
            qApp->processEvents();
        }
        m_status->clear(); //清空数据，重新开始
        m_status->runPath();
        m_status->runLidar();
        m_ml->update();
        break;
    }
    case Qt::Key_Up:
        // this->moveView(0, -1);
        m_ml->moveBy(0, -10);
        // m_ml->update();
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
    qreal w, h;
    qreal mx, my;

    qreal factor = transform().scale(1, 1).mapRect(QRectF(0, 0, 1, 1)).width();
    printf("factor = %f\n", factor);

    QRectF sceneRect = this->sceneRect();

    w = sceneRect.width();
    h = sceneRect.height();

    mx = dx * w / 10.0;
    my = dy * h / 10.0;

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
