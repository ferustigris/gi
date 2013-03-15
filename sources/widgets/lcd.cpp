#include "lcd.h"
#include <QHBoxLayout>

LcdLabel::LcdLabel(MainWindow* mw, Log*log) : Widget(mw, log)
{
        l = new QLCDNumber(this);
        l->show();
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(l);
        setLayout(layout);
        setWindowTitle(tr("LcdLabel"));
}
LcdLabel::~LcdLabel()
{
    delete l;
}
//! set value (different for different widgets)
void LcdLabel::setValue(const QByteArray& data)
{
    qint16 size = 4;
    float value = 0;
    if(data.size() < 4)
    {
        addError(tr("Led: short msg!"));
        return;
    }
    memcpy(&value, data.data(), size);
    l->display(value);
    addMsg(tr("Lcd: Receive floationg point value: ") + QString::number(value));
}
