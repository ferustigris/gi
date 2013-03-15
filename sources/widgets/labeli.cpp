#include "labeli.h"

LabelI::LabelI(MainWindow* mw, Log*log) : Label(mw, log)
{
	setWindowTitle(tr("Integer value"));
}
//! set value (different for different widgets)
void LabelI::setValue(const QByteArray& data)
{
    qint16 size = 4;
    qint32 value = 0;
    if(data.size() < 4)return;
    memcpy(&value, data.data(), size);
    QString str(QString::number(value));
    l->setText(str);
    addMsg(tr("Receive integer value: ") + str);
}
