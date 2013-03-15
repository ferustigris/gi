#ifndef LcdLabel_H
#define LcdLabel_H
#include <QLCDNumber>
#include "widget.h"

class LcdLabel : public Widget
{
public:
        LcdLabel(MainWindow* mw, Log*log);
        virtual ~LcdLabel();
        virtual void setValue(const QByteArray& data);
protected:
        QLCDNumber *l;
};

#endif // LcdLabel_H
