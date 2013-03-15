#include "led.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
Led::Led(MainWindow* mw, Log*log) : Widget(mw, log), ok(":/widgets/led/ok"), off(":/widgets/led/off"),
    warning(":/widgets/led/warning"), alarm(":/widgets/led/alarm")
{
        l = new QLabel("asd", this);
        state = OFF;
        l->show();
        l->setScaledContents (true);
	QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(l);
        setLayout(layout);
        setWindowTitle(tr("Led"));
        l->setIndent(16);
}
Led::~Led()
{
    delete l;
}
//! set value (different for different widgets)
void Led::setValue(const QByteArray& data)
{
    QString str("");
    qint8 oper = 0;
    if(data.size() < 1)
    {
        addError(tr("Led: short msg!"));
        return;
    }
    memcpy(&oper, data.data(), 1);
    switch(oper)
    {
        case NAME:
        {
            QByteArray astr(data.size() - 1, 0);
            memcpy(astr.data(), data.data()+1, astr.size());
            l->setText(QString(astr));
            addMsg(tr("Led: Set name: ") + str);
            break;
        }
        case STATE:
            if(data.size() < 2)
            {
                addError(tr("Led: short msg!"));
                return;
            }
            memcpy(&oper, data.data()+1, 1);
            addMsg(tr("Led: Set state: ") + oper);
            state = (States)oper;
            repaint();
            break;
        default:
            ;;
    }
}
//!процедура перерисовки
void Led::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);
            switch(state)
            {
                case OFF:
                    painter.drawImage(4,event->rect().height() / 2 - off.height() / 2 , off);
                    break;
                case OK:
                    painter.drawImage(4,event->rect().height() / 2 - ok.height() / 2 , ok);
                    break;
                case WARNING:
                    painter.drawImage(4,event->rect().height() / 2 - warning.height() / 2 , warning);
                    break;
                default:
                    painter.drawImage(4,event->rect().height() / 2 - alarm.height() / 2 , alarm);
                ;;
            }
    QWidget::paintEvent(event);
}
