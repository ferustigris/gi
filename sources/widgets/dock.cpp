#include "sources/widgets/dock.h"
#include <QVBoxLayout>
#include "mainwindow.h"

Dock::Dock(MainWindow* mw, Log*log) : Widget(mw, log)
{
	layout = new QVBoxLayout;
	setLayout(layout);
	this->mw = mw;
	setWindowTitle(tr("Control panel"));
	setWindowIcon(QIcon(":/icons/logview"));
}
//! destructor
Dock::~Dock()
{
}
//! set value (different for different widgets)
void Dock::setValue(const QByteArray& data)
{
	addMsg(tr("control panel"));
	QString str("");
	if(data.size() <= 1)return;
	qint8 c;
	memcpy(&c, data.data(), 1);
	switch(c)
	{
	case ADD_ITEM:
		for(int i = 1; i < data.size(); i++)
		{
			memcpy(&c, data.data() + i, 1);
                        if(QWidget*w = mw->getById(mw->getUniqId(c, getPort(), getIP())))
			{
                                layout->addWidget(w);
                                str += QString::number(c);
			}
		}
		break;
	case SET_TITLE:
		QByteArray ar(data.size() - 1, 0);
                memcpy(ar.data(), data.data()+1, ar.size());
		str = QString(ar);
                setWindowTitle(str);
		break;
	}
	addMsg(tr("Add to control panel") + str);
}
