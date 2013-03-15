#include "widget.h"
#include "mainwindow.h"

//! constructor
Widget::Widget(MainWindow* mw, Log*log) : QWidget()
{
	setWindowFlags(Qt::Drawer);
	this->log = log;
	this->mw = mw;
}
//! destructor
Widget::~Widget()
{
}
//! set value (different for different widgets)
void Widget::setValue(const QByteArray& data)
{
	Q_UNUSED(data);
}
//! send value, simple transfer this data to PLIS
void Widget::sendValue(const QByteArray& data)
{
	QByteArray datagram(data.size() + 3, 0);
	memcpy(datagram.data() + 3, data.data(), data.size());
	memcpy(datagram.data(), &id, 1);
	memcpy(datagram.data() + 1, &type, 1);
	memcpy(datagram.data() + 2, &id, 1);
	mw->send(host, port, datagram);
}
//! add to log
void Widget::addMsg(const QString&msg)
{
        if(log)
                log->addMsg(msg);
}
//! add to log
void Widget::addError(const QString&msg)
{
        if(log)
                log->addMsg(msg);
}
//! установить адрес виджета
void Widget::setAddress(const qint8 id, const qint8 type, const QHostAddress& host, const quint16 port)
{
	this->host = host;
	this->port = port;
	this->id = id;
	this->type = type;
}
qint32 Widget::getIP() const
{
    return host.toIPv4Address();
}
qint16 Widget::getPort() const
{
    return port;
}



















