#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include "widget.h"

class Label : public Widget
{
public:
	enum ControlSymbols {
		I = 0x01,
		F,//0x02
                HEX,//0x03
	};
	Label(MainWindow* mw, Log*log);
	virtual ~Label();
	virtual void setValue(const QByteArray& data);
protected:
	QLabel *l;
};

#endif // LABEL_H
