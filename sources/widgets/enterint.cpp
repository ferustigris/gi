#include "enterint.h"
#include <QHBoxLayout>
#include <QByteArray>

//! constructor
EnterInt::EnterInt(MainWindow* mw, Log*log):
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
	setWindowTitle(tr("Enter integer number"));
}
//! destructor
EnterInt::~EnterInt()
{
	delete button;
	delete edit;
}
//! edited text
void EnterInt::textChanged ( const QString & text)
{
	bool ok = false;
	qint32 tmp = text.toInt(&ok);
	if(ok)
		value = tmp;
	else
		edit->setText(QString::number(value));
}
//! press on enter
void	EnterInt::pressed ()
{
	QByteArray data(4,0);
	memcpy(data.data(), &value, 4);
	this->sendValue(data);
}
//! set value (different for different widgets)
void EnterInt::setValue(const QByteArray& data)
{
    qint16 size = 4;
    qint32 value = 0;
    if(data.size() < 4)return;
    memcpy(&value, data.data(), size);
    QString str(QString::number(value));
    edit->setText(str);
    addMsg(tr("Edit: Receive int value: ") + str);
}
