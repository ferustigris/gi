#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "label.h"
#include "labelf.h"
#include "labeli.h"
#include "led.h"
#include "dial.h"
#include "dock.h"
#include "enterfloat.h"
#include "enterint.h"
#include "graph.h"
#include "lcd.h"
#include <QTime>
#include <QMessageBox>
#include <QApplication>
#include <QWebView>

MainWindow::MainWindow(QObject *parent)
    : QSystemTrayIcon(parent), timer(), addr(QHostAddress::Broadcast), log(0)
{
    countOperations = 0;
    countRecPack = 0;
    countSendPack = 0;
    localPort = 45454;
    time(&commonTime);
    LOG(LOG_DEBUG, "start", 0, "./main.log");
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    timer.start(1000);
    udpSocket.bind(localPort);
    setIcon(QIcon(":/icons/main"));
    setContextMenu(&ppTopMenu);
    QAction *log = new QAction(QIcon(":/icons/log"), tr("Show log"), this);
    connect(log, SIGNAL(triggered()), this, SLOT(on_log()));
    ppTopMenu.addAction(log);
    QAction *clear = new QAction(QIcon(":/icons/new"), tr("Clear"), this);
    connect(clear, SIGNAL(triggered()), this, SLOT(on_clear()));
    ppTopMenu.addAction(clear);
    QAction *help = new QAction(QIcon(":/icons/help"), tr("Help"), this);
    connect(help, SIGNAL(triggered()), this, SLOT(on_help()));
    ppTopMenu.addAction(help);
    QAction *exit = new QAction(QIcon(":/icons/exit"), tr("Exit"), this);
    connect(exit, SIGNAL(triggered()), this, SLOT(on_close()));
    ppTopMenu.addSeparator();
    ppTopMenu.addAction(exit);
    setToolTip(tr("Show widgets from PLIS"));
    //QMessageBox::information(0, "", QString::number(' '));
}

MainWindow::~MainWindow() {
    foreach(Widget*w, widgets.values())
	delete w;
}
//событие выхода
void MainWindow::on_close() {
    hide();
    exit(0);
}
//событие очистки
void MainWindow::on_clear() {
    foreach(Widget*w, widgets.values())
	delete w;
    widgets.clear();
}
//показать помощь
void MainWindow::on_help() {
	static QWebView *webView = new QWebView;
	webView->setAttribute(Qt::WA_QuitOnClose, false);
#ifdef Q_OS_WIN32
	webView->setUrl(QApplication::applicationDirPath() + "/../share/help/help.html");
#endif
#ifdef Q_OS_LINUX
	webView->setUrl(QApplication::applicationDirPath() + "/share/help/help.html");
#endif
	webView->show();
	webView->setWindowTitle(tr("About protocol"));
	//QMessageBox::information(0, "", webView.url().toString());
}
//событие показать лог
void MainWindow::on_log() {
    log.show();
}
void MainWindow::on_timer() {
    /*time_t curTime;
    time(&curTime);
    curTime -= commonTime;
    ui->leAnswer->setText(QString::number(answer1) + " " + QString::number(answer2) + " " + QString::number(answer3) + " " + QString::number(answer4));
    ui->log->setText(QString("Iterations: ") + QString::number(countOperations)
		       + "\nsend packets: "+ QString::number(countSendPack)
		       + "\nreceive packets: "+ QString::number(countRecPack)
		       + "\naverage speed: "+ (curTime ? QString::number(countRecPack/curTime) : "0")+" op/sec");
		       */
}
//прием датаграмм
void MainWindow::processPendingDatagrams() {
	LOG(LOG_DEBUG,"TCore::processPendingDatagrams");
	static QByteArray datagram;
	static QHostAddress addr;
	static quint16 port;
	static quint32 id;//fuul id
	static quint8 idw;//id of concretic widget
	static qint8 wType;//type of widget
	WidgetType wt;
	Operation op;
	while (udpSocket.hasPendingDatagrams())
	{
		datagram.resize(udpSocket.pendingDatagramSize());
		udpSocket.readDatagram(datagram.data(), datagram.size(), &addr, &port);
		showMessage(tr("Receive packet"), tr("Packet from ") + addr.toString(), QSystemTrayIcon::Information, 2000);
		if(datagram.length() >= 1)
		{
			memcpy(&idw, datagram.data(), 1);
			//QMessageBox::information(0, "!" + QString::number(idw), QString::number(id));
		}
		else continue;
		//type od widget
		if(datagram.length() >= 2)
		    memcpy(&wType, datagram.data()+1, 1);
		else continue;
		wt = (WidgetType)wType;
		//QMessageBox::information(0, "wt", QString::number(wt) + ", " + QString::number(wType));
		//operation
		if(datagram.length() >= 3)
			memcpy(&wType, datagram.data()+2, 1);
		else continue;
		op = (Operation)wType;
		QString msg(tr("Receive packet from %1").arg(addr.toString() + ":" + QString::number(port)));
		for(int i = 0; i < datagram.length(); i++)
			msg += " 0x" + QString::number(datagram.at(i), 16);
		log.addMsg(msg);
		//получаем число, зависящее от первого знака ip-адреса, от порта и индивидуального номера виджета
		id = getUniqId(idw, port, addr.toIPv4Address());
		//QMessageBox::information(0, QString::number(idw), QString::number(id));
		Widget *widget;
		if(widgets.contains(id))//к виджету уже было обращение
		{
			widget = widgets[id];
		}
		else
		{
			switch(wt)
			{
			case LABEL:
				//QMessageBox::information(0, QString::number(wt), "LABEL");
				widget = new Label(this, &log);
				break;
			case LABELF:
				//QMessageBox::information(0, QString::number(wt), "LABELf");
				widget = new LabelF(this, &log);
				break;
			case LABELI:
				//QMessageBox::information(0, QString::number(wt), "LABELi");
				widget = new LabelI(this, &log);
				break;
			case GRAPH:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new Graph(this, &log);
				break;
			case LIST:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new List(this, &log);
				break;
			case ENTER_FLOAT:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new EnterFloat(this, &log);
				break;
			case LED:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new Led(this, &log);
				break;
			case ANALOG_DIAL:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new Dial(this, &log);
				break;
			case DOCK:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new Dock(this, &log);
				break;
			case LCD_LABEL:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new LcdLabel(this, &log);
				break;
			case ENTER_INT:
				//QMessageBox::information(0, QString::number(wt), "graph");
				widget = new EnterInt(this, &log);
				break;
			default:
				//QMessageBox::information(0, QString::number(wt), "def");
				widget = NULL;//new Widget(this, &log);
				continue;
			}
			widget->setAddress(idw, wt, addr, port);
			widgets.insert(id, widget);
		}
		try
		{
		    widget->isEnabled();
		} catch(...)
		{
		    continue;
		}
		switch(op)
		{
		case KOORD:
			{//координаты
				static qint16 x,y,w,h;
				if(datagram.length() > 4)
					memcpy(&x, datagram.data()+3, 2);
				else continue;
				if(datagram.length() > 6)
					memcpy(&y, datagram.data()+5, 2);
				else continue;
				if(datagram.length() > 8)
					memcpy(&w, datagram.data()+7, 2);
				else continue;
				if(datagram.length() > 10)
					memcpy(&h, datagram.data()+9, 2);
				else continue;
				log.addMsg(tr("Move widget: (%1, %2, %3, %4)").arg(x).arg(y).arg(w).arg(h));
				widget->setGeometry(x,y,w,h);
			}
			widget->show();
			break;
		case VALUE:
			{
			int size = datagram.size()-3;
			if(size > 0)
			{
				QByteArray data(size, 0);
				memcpy(data.data(), datagram.data()+3, size);
				widget->setValue(data);
			}
			else continue;
			}
			widget->show();
			break;
		case CLOSE:
			log.addMsg(tr("Hide widget"));
			widget->hide();
			break;
		case SHOW:
			log.addMsg(tr("Show widget"));
			widget->show();
			break;
		case SET_TITLE:
			log.addMsg(tr("Set title"));
			{
				QString title ("");
				int size = datagram.size()-3;
				if(size > 0)
				{
					QByteArray data(size, 0);
					memcpy(data.data(), datagram.data()+3, size);
					title = QString (data);
				}
				widget->setWindowTitle(title);
			}
			break;
		default:
			log.addMsg(tr("Unknown command!"));
		}
		countRecPack++;
	}
}
void MainWindow::send(const QHostAddress&address, quint16 port, const QByteArray& data)
{
	//QMessageBox::information(0, "", address.toString() + " " + QString::number(port));
	udpSocket.writeDatagram(data, address, port);
}
//! get widget from list by id. if no exists, then null return.
QWidget* MainWindow::getById(const qint32 id) const
{
    if(widgets.contains(id))
    {
	return widgets[id];
    }
    else return NULL;
}
//!return unique id, depended from first byte IP, port and id
qint32 MainWindow::getUniqId(qint8 id, qint16 port, qint32 ip) const
{
	qint32 result = ip;
	memcpy(&result + 1, &port, 2);
	memcpy(&result, &id, 1);
	return result;
}




















