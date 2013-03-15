#ifndef GRAPH_H
#define GRAPH_H
#include "widget.h"

#include <QtGui/QWidget>

namespace Ui {
    class Graph;
}

class Graph : public Widget {
    Q_OBJECT
    Q_DISABLE_COPY(Graph)
public:
    explicit Graph(MainWindow* mw, Log*log, QWidget *parent = 0);
    virtual ~Graph();
    virtual void setValue(const QByteArray& data);
    enum CommandTypes {
        ADD_KOORD = 0,
        SETXTITLE,
        SETYTITLE,
    };
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Graph *m_ui;
    QPoint lastPos;
};

#endif // GRAPH_H
