#ifndef Dial_H
#define Dial_H
#include <QLabel>
#include "widget.h"
#include <QDial>

class Dial : public Widget
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
        Dial(MainWindow* mw, Log*log);
        virtual ~Dial();
	virtual void setValue(const QByteArray& data);
protected:
        QDial *l;
};

#endif // Dial_H
