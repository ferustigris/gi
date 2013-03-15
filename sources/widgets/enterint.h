#ifndef EnterInt_H
#define EnterInt_H
#include <QLabel>
#include "widget.h"
#include <QLineEdit>
#include <QPushButton>

class EnterInt : public Widget
{
	Q_OBJECT
public:
	EnterInt(MainWindow* mw, Log*log);
	~EnterInt();
	virtual void setValue(const QByteArray& data);
private:
	QPushButton *button;
	QLineEdit *edit;
	qint32 value;
private slots:
	void textChanged ( const QString & text );
	void	pressed ();
};

#endif // EnterInt_H
