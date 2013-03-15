#ifndef LIST_H
#define LIST_H
#include <widget.h>
#include <QPlainTextEdit>

class List : public Widget
{
public:
	enum ControlSymbols {
		I = 0x01,
		F,//0x02
                HEX,//0x03
	};
	List(MainWindow* mw, Log*log);
	~List();
	virtual void setValue(const QByteArray& data);
private:
	QPlainTextEdit *l;
};

#endif // LIST_H
