#ifndef ENTERFLOAT_H
#define ENTERFLOAT_H
#include <QLabel>
#include "widget.h"
#include <QLineEdit>
#include <QPushButton>

class EnterFloat : public Widget
{
	Q_OBJECT
public:
	EnterFloat(MainWindow* mw, Log*log);
	~EnterFloat();
	virtual void setValue(const QByteArray& data);
private:
	QPushButton *button;
	QLineEdit *edit;
	float value;
private slots:
	void textChanged ( const QString & text );
	void	pressed ();
};

#endif // ENTERFLOAT_H
