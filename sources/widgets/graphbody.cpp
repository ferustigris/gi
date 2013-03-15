#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include "graphbody.h"
#include <QWheelEvent>
#include "errors.h"
#include <QMessageBox>

/*!\func TGraph::TGraph
 * конструктор класса-поля-окна, где будет рисоваться граф
 * \param
 * - parent - родитель
 * \return нет
 */
GraphBody::GraphBody(QWidget*parent) :
    scene()
{
    Q_UNUSED(parent);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(&scene);
    setRenderHint(QPainter::Antialiasing);
    //setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorUnderMouse);
    //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    //сжатие графика
    minx = -100;
    miny = -75;
    maxx = 100;
    maxy = 75;
    x_title = tr("Ox");
    y_title = tr("Oy");
    OxTitle = new QGraphicsTextItem(x_title);
    OyTitle = new QGraphicsTextItem(y_title);
    Ox = new QGraphicsLineItem(minx, 0, maxx, 0);
    Oy = new QGraphicsLineItem(0, miny, 0, maxy);
    OxO = new QGraphicsTextItem("0");
    OxO->setPos(0,0);
    avgX = new QGraphicsTextItem(QString::number(maxx/2));
    avgX->setPos(maxx/2, 0);
    avgY = new QGraphicsTextItem(QString::number(-miny/2));
    avgY->setPos(0, miny/2);
    OyTitle->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    OxTitle->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    OxO->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    avgX->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    avgY->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    Ox->setPen(QPen(Qt::gray));
    Oy->setPen(QPen(Qt::gray));
    scene.addItem(Ox);
    scene.addItem(OxO);
    scene.addItem(avgX);
    scene.addItem(avgY);
    scene.addItem(Oy);
    scene.addItem(OxTitle);
    scene.addItem(OyTitle);
    oldw = maxx-minx;
    oldh = maxy-miny;
    neww = oldw;
    newh = oldh;
    centerOn(0,0);
    setAlignment(Qt::AlignCenter);
    scale(1.,1.);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    first = false;
}
/*!\func TGraph::TGraph
 * деструктор
 * \param нет
 * \return нет
 */
GraphBody::~GraphBody()
{
    LOG(LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    scene.clear();
}
qreal GraphBody::checkRate(const QPoint& p)
{
    if(p.x() > maxx) maxx = p.x();
    if(p.y() > maxy) maxy = p.y();
    if(p.x() < minx) minx = p.x();
    if(p.y() < miny) miny = p.y();
    neww = maxx-minx;
    newh = maxy-miny;
    if(OxTitle&&OyTitle)
    {
        OxTitle->setPos(maxx - maxx/10, 0);
        OyTitle->setPos(0, miny + miny/10);
    }
    if(avgX&&avgY)
    {
        avgX->setPos(maxx/2, 0);
        avgY->setPos(0, miny/2);
    }
    Ox->setLine(minx, 0, maxx, 0);
    Oy->setLine(0, miny, 0, maxy);
    return 0;
}
void GraphBody::resizeEvent(QResizeEvent * event)
{
    if(first)
    {
	qreal w = 1;
	if(event->oldSize().width())
	    w = (qreal)event->size().width()/(qreal)event->oldSize().width();
	qreal h = 1;
	if(event->oldSize().height())
	    h = (qreal)event->size().height()/(qreal)event->oldSize().height();
	if(!w)w = 1;
	if(!h)h = 1;
	scale(w, h);
    }
    else first = true;
    //QWidget::resizeEvent(event);

}
void GraphBody::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
	scale(1.1, 1.1);
    else
	scale(0.9, 0.9);
}
//очстить
void GraphBody::cl()
{
    scene.clear();
    resetTransform();
    minx = -100;
    miny = -75;
    maxx = 100;
    maxy = 75;
    oldw = maxx-minx;
    oldh = maxy-miny;
    neww = oldw;
    newh = oldh;
    OxTitle = new QGraphicsTextItem(tr("Ox"));
    OyTitle = new QGraphicsTextItem(tr("Oy"));
    Ox = new QGraphicsLineItem(minx, 0, maxx, 0);
    Oy = new QGraphicsLineItem(0, miny, 0, maxy);
    OxO = new QGraphicsTextItem("0");
    avgX = new QGraphicsTextItem(QString::number(maxx/2));
    avgX->setPos(maxx/2, 0);
    avgY = new QGraphicsTextItem(QString::number(-miny/2));
    avgY->setPos(0, miny/2);
    OyTitle->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    OxTitle->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    Ox->setPen(QPen(Qt::gray));
    Oy->setPen(QPen(Qt::gray));
    OxO->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    avgX->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    avgY->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    scene.addItem(Ox);
    scene.addItem(Oy);
    scene.addItem(OxTitle);
    scene.addItem(OyTitle);
    scene.addItem(OxO);
    scene.addItem(avgX);
    scene.addItem(avgY);
    centerOn(0,0);
    setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    scale(2.1,1.);
}
//! add new item
void GraphBody::addItem(QGraphicsItem*item)
{
    scene.addItem(item);
    qreal delw = (qreal)oldw/(qreal)neww;
    qreal delh = (qreal)oldh/(qreal)newh;
    if(!delw)delw=1;
    if(!delh)delh=1;
    scale(delw, delh);
    oldw = maxx-minx;
    oldh = maxy-miny;
    if(OxTitle)OxTitle->setPlainText(QString::number(maxx-maxx/10) + "\n" + x_title);
    if(OyTitle)OyTitle->setPlainText(y_title + '\n' + QString::number(-miny));
    if(avgX)avgX->setPlainText(QString::number(maxx/2));
    if(avgY)avgY->setPlainText(QString::number(-miny/2));
}
void GraphBody::setOyTitle(const QString &title)
{
    //if(OyTitle)OyTitle->setPlainText(title);
    y_title = title;
}
void GraphBody::setOxTitle(const QString &title)
{
    //if(OxTitle)OxTitle->setPlainText(title);
    x_title = title;
}
