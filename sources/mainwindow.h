#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSystemTrayIcon>
#include <QMenu>
#include <QtNetwork/QUdpSocket>
#include <QTimer>
#include <QMap>
#include "errors.h"
#include "widget.h"
#include "log.h"
#include "list.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QSystemTrayIcon {
	Q_OBJECT
public:
	enum WidgetType {
		LABEL = 0,
		LABELF,//0x01
		LABELI,//0x02
		GRAPH,//0x03
		LIST,//0x04
		ENTER_FLOAT,//0x05
		LED,//0x06
		ANALOG_DIAL,//0x07
		DOCK,//0x08 - panel,
		LCD_LABEL,//0x09 - LCD printf
		ENTER_INT,//0xA0 - enter integer
	};
	enum Operation {
		KOORD = 0,
		VALUE,//0x01
		CLOSE,//0x02
		SHOW,//0x03
		SET_TITLE,//0x04 - set window title
	};
	MainWindow(QObject *parent = 0);
	~MainWindow();
	void send(const QHostAddress&address, quint16 port, const QByteArray& data);
	QWidget* getById(const qint32 id) const;
	qint32 getUniqId(qint8 id, qint16 port, qint32 ip) const;
private:
	Ui::MainWindow *ui;
	QUdpSocket udpSocket;//соккет для общения с платой
	quint16 localPort;
	int countOperations;
	int countRecPack;
	int countSendPack;
	time_t commonTime;
	QTimer timer;
	QHostAddress addr;
	QMap<quint32, Widget* > widgets;
	QMenu ppTopMenu;
	Log log;
private slots:
	void processPendingDatagrams();
	void on_timer();
	void on_close();
	void on_clear();
	void on_help();
	void on_log();
};

#endif // MAINWINDOW_H
