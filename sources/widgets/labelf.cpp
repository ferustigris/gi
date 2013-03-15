#include "labelf.h"

LabelF::LabelF(MainWindow* mw, Log*log) : Label(mw, log)
{
	setWindowTitle(tr("Floating point value"));
}
//! set value (different for different widgets)
void LabelF::setValue(const QByteArray& data)
{
    qint16 size = 4;
    float value = 0;
    if(data.size() < 4)
    {
        addError(tr("Led: short msg!"));
        return;
    }
    memcpy(&value, data.data(), size);
    QString str(QString::number(value));
    l->setText(str);
    addMsg(tr("Receive floationg point value: ") + str);
}
