#ifndef Led_H
#define Led_H
#include <QLabel>
#include "widget.h"
#include <QImage>

class Led : public Widget
{
public:
        enum ControlSymbols {
                NAME = 0x00,
                STATE,//0x01
        };
        enum States {
                OFF = 0x00,
                OK,//0x01
                WARNING,//0x02
                ALARM,//0x03
        };
        Led(MainWindow* mw, Log*log);
        virtual ~Led();
	virtual void setValue(const QByteArray& data);
protected:
        QLabel *l;
private:
        States state;
        QImage ok, off, warning, alarm;
        virtual void paintEvent ( QPaintEvent * event );
};

#endif // Led_H
