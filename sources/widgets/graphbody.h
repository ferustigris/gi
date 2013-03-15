#ifndef GRAPHBODY_H
#define GRAPHBODY_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QSharedData>
#include <QTimer>
#include <QObject>

//виджет для отображения графа
class GraphBody : public QGraphicsView {
public:
    explicit GraphBody(QWidget*parent);
    virtual ~GraphBody();
    void addItem(QGraphicsItem*item);
    void setOyTitle(const QString &title);
    void setOxTitle(const QString &title);
    qreal checkRate(const QPoint& p);
private:
    QGraphicsScene scene;
    int maxx;
    int maxy;
    int minx;
    int miny,
	oldw, neww,
	oldh, newh;
    bool first;
    QGraphicsTextItem *OxTitle, *OyTitle, *OxO, *avgX, *avgY;
    QGraphicsLineItem *Ox, *Oy;
    QString y_title, x_title;
protected:
    void resizeEvent ( QResizeEvent * event );
    void wheelEvent(QWheelEvent *event);
    QList<QGraphicsLineItem*> items;
    void cl();
};

#endif // GRAPHBODY_H
