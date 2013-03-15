#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QHostAddress>
#include "log.h"

class MainWindow;

class Widget : public QWidget
{
public:
    Widget(MainWindow* mw, Log*log);
    virtual ~Widget();
    virtual void setValue(const QByteArray& data);//! set value (different for different widgets)
    void sendValue(const QByteArray& data);//! send value to PLIS
    void setAddress(const qint8 id, const qint8 type, const QHostAddress& host, const quint16 port);
protected:
    void addMsg(const QString&msg);
    void addError(const QString&msg);
    qint32 getIP() const;
    qint16 getPort() const;
private:
    MainWindow* mw;
    Log*log;
    QHostAddress host;
    quint16 port;
    qint8 id, type;
};

#endif // WIDGET_H
