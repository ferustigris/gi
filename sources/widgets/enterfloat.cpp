#include "enterfloat.h"
#include <QHBoxLayout>
#include <QByteArray>

//! constructor
EnterFloat::EnterFloat(MainWindow* mw, Log*log):
	Widget(mw, log)
{
	edit = new QLineEdit("0", this);
	edit->show();
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(edit);
	button = new QPushButton(tr("Enter"), this);
	button->show();
	layout->addWidget(button);
	setLayout(layout);
	connect(edit, SIGNAL(textChanged ( const QString & )), this, SLOT(textChanged ( const QString & )));
	connect(button, SIGNAL(pressed ()), this, SLOT(pressed()));
	value = 0;
	setWindowTitle(tr("Enter floating point number"));
}
//! destructor
EnterFloat::~EnterFloat()
{
	delete button;
	delete edit;
}
//! edited text
void EnterFloat::textChanged ( const QString & text)
{
	bool ok = false;
	float tmp = text.toFloat(&ok);
	if(ok)
		value = tmp;
	else
		edit->setText(QString::number(value));
}
//! press on enter
void	EnterFloat::pressed ()
{
	QByteArray data(4,0);
	memcpy(data.data(), &value, 4);
	this->sendValue(data);
}
//! set value (different for different widgets)
void EnterFloat::setValue(const QByteArray& data)
{
    qint16 size = 4;
    double value = 0;
    if(data.size() < 4)return;
    memcpy(&value, data.data(), size);
    QString str(QString::number(value));
    edit->setText(str);
    addMsg(tr("Edit: Receive floationg point value: ") + str);
}
