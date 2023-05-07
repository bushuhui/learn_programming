/****************************************************************************
****************************************************************************/

#include <stdio.h>

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

#include "pmap_viewer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MapLayer::MapLayer(MapViewer *mv, RMap *map, State *state, Simulation *simulation) //初始化maplayer
{
    m_map = map;
    m_mv = mv;
    m_state = state;
    simulation = m_simulation;
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
    if (m_mv->pathswitch)
    {
        RPath pathres;
        pathres = m_state->getPath();
        if (pathres.size() != 0)
        {
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
        }
    }

    // draw lidar_detect area
    if (m_mv->lidarswitch)
    {
        Rlidar lidarres;
        lidarres = m_state->getLidar();
        if (lidarres.size() != 0)
        {
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
        }
    }

    // draw track
    if (m_mv->trackswitch)
    {
        RPath track;
        track = m_state->getTrack();
        if (track.size() != 0)
        {
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
        }
    }

    // draw current position
    m_state->getLoc(&ix, &iy);
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
    //设置开关
    moveswitch = 0;
    showswitch = 0;
    clearswitch = 0;
    menuswitch = 0;

    // init map data
    m_map = new RMap(100, 100);

    // FIXME: if possible, add a menu item (also a key press event) to call the file selection
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), "", tr("map(*.map);;Allfile(*.*)"));
    char *mapFileName;
    QByteArray ba = fileName.toLatin1(); // must
    mapFileName = ba.data();             // QString to char*

    int loadswitch = m_map->loadMap(mapFileName);
    if (loadswitch == 0)
        showswitch = 1; //地图成功加载，可显示
    else
        showswitch = 0;

    m_state = new State(m_map);
    m_simulation = new Simulation(m_state); //创建仿真类对象

    m_simulation->createSub(m_simulation); //创建子线程

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

    m_ml = new MapLayer(this, m_map, m_state, m_simulation); //状态、仿真加入
    m_ml->setPos(0, 0);
    scene->addItem(m_ml);
}

void MapViewer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_S: //按S显示路径和探测结果
    {
        if (showswitch)
        {
            m_state = m_simulation->show();
            pathswitch = 1;
            lidarswitch = 1;
            trackswitch = 1;
            m_ml->update();
            moveswitch = 1; //显示成功，可移动
        }
    }
    case Qt::Key_M: //按M进行点的移动
    {
        // FIXME: it is require to determin the map is load or not
        if (moveswitch)
        {
            RPath pathres;
            pathres = m_simulation->pathPlan();
            for (int i = 0; i < pathres.size(); i++)
            {
                m_state = m_simulation->pointMove(pathres[i].x, pathres[i].y);
                m_state = m_simulation->lidarScan();
                m_ml->update();
                qApp->processEvents();
            }
            clearswitch = 1; //移动成功，可清理重做
        }

        break;
    }
    case Qt::Key_C: //按C回到原点
    {
        if (clearswitch)
        {
            m_state = m_simulation->remake();
            m_ml->update();
        }
    }
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
