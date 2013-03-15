#include "graph.h"
#include "ui_graph.h"

Graph::Graph(MainWindow* mw, Log*log, QWidget *parent) :
    Widget(mw, log),
    m_ui(new Ui::Graph), lastPos(0,0)
{
	Q_UNUSED(parent);
	m_ui->setupUi(this);
	setWindowTitle(tr("Graphic"));
}

Graph::~Graph()
{
    delete m_ui;
}

void Graph::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
	m_ui->retranslateUi(this);
	break;
    default:
	break;
    }
}
//! set value (different for different widgets)
void Graph::setValue(const QByteArray& data)
{
	//QMessageBox::information(0, "1", "receive data!");
        int i = 1;
	QString str("");
        qint8 oper = 0;
        memcpy(&oper, data.data(), 1);
        CommandTypes comType = (CommandTypes)oper;
        switch(comType) {
        case ADD_KOORD:
            while(i <= data.length() - 8)
            {
                    qint32 x, y;
                    memcpy(&x, data.data() + i, 4);
                    i += 4;
                    memcpy(&y, data.data() + i, 4);
                    y = -y;
                    i += 4;
                    str += "(" + QString::number(x) + ", " + QString::number(y) + "), " ;
                    QPoint p(x, y);
                    QGraphicsLineItem *i = new QGraphicsLineItem(lastPos.x(), lastPos.y(), p.x(), p.y());
                    QPen pen(Qt::blue);
                    pen.setWidth(2);
                    i->setPen(pen);
                    m_ui->widget->addItem(i);
                    lastPos = p;
                    m_ui->widget->checkRate(p);
            }
            addMsg(tr("Add points to graphic: ") + str);
            break;
        case SETXTITLE:
        case SETYTITLE:
            {
                QByteArray raw(data.size() - 1, 0);
                memcpy(raw.data(), data.data() + 1, raw.size());
                QString str(raw);
                if(comType == SETXTITLE)
                    m_ui->widget->setOxTitle(str);
                else
                    m_ui->widget->setOyTitle(str);
                addMsg(tr("Set title graphic: ") + str);
            }
            break;
        default:
            addMsg(tr("graphic: no operation"));
            ;
        }
}
