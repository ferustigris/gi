#include "dial.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
Dial::Dial(MainWindow* mw, Log*log) : Widget(mw, log)
{
        l = new QDial(this);
        l->show();
        l->setNotchesVisible(true);
	QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(l);
        setLayout(layout);
        setWindowTitle(tr("Dial"));
}
Dial::~Dial()
{
    delete l;
}
//! set value (different for different widgets)
void Dial::setValue(const QByteArray& data)
{
    QString str("");
    qint32 oper = 0;
    if(data.size() != 4)
    {
        addError(tr("Dial: short msg!"));
        return;
    }
    memcpy(&oper, data.data(), 4);
    l->setValue(oper);
    addMsg(tr("Dial: set value:") + QString::number(oper));
}
