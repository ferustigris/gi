#include "core.h"
#include <QDir>
#include <QVariant>
//#include <QtGui/QApplication>
//#include <QPluginLoader>
#include "jobsnames.h"
#include "mainwindow.h"
#include "list.h"
#include "math.h"
/*!\func TCore
 * конструктор класса
 * \param нет
 * \return нет
 */
TCore::TCore(const QString &newPluginsDir, quint16 localPort) : address(QHostAddress::Broadcast), timer() {
//    qDebug()<<"TCore";
    this->pluginsDir = newPluginsDir;
    //уникальный типа »ƒ
    unique_id = 1;
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    timer.start(1000);
    //создаем соккет
    this->localPort = localPort;
    remoutePort = 45454;
    udpSocket.bind(localPort);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}
void TCore::on_timer() {
	qDebug ()<<__FUNCTION__;
    label_and_move();
    labelF();
    labelI_and_hide();
    list();
    enterF();
    window_title();
    enterI();
    graph();
    led();
    dial();
    lcd_label();

}
/*!\func ~TCore
 * деструктор класса
 * \param нет
 * \return нет
 */
TCore::~TCore() {
    //закрываем сокет
    udpSocket.close();
}
/*!\func processPendingDatagrams
 * обработчик событи€ "пришли данные из сокета"
 * \param нет
 * \return нет
 */
void TCore::processPendingDatagrams() {
    //qDebug()<<"processPendingDatagrams";
    static QHostAddress address;
    static QByteArray datagram, data(16,0);
    static quint16 port;
    static qint8 oper1 = 1;
    while (udpSocket.hasPendingDatagrams()) {
	//qDebug()<<"reading...";
	datagram.resize(udpSocket.pendingDatagramSize());
	udpSocket.readDatagram(datagram.data(), datagram.size(), &address, &port);
	if(datagram.size()  < 7)continue;
	memcpy(&oper1, datagram.data(), 1);
	memcpy(&oper1, datagram.data()+1, 1);
	if (oper1 == ENTER_FLOAT)
	{
		memcpy(&oper1, datagram.data()+2, 1);
		float value = 0;
		memcpy(&value, datagram.data()+3, 4);
		qDebug()<<"receive float:"<<value;
		//qDebug()<<value;
		dock();
	} else if(oper1 == ENTER_INT)
	{
		memcpy(&oper1, datagram.data()+2, 1);
		qint32 value = 0;
		memcpy(&value, datagram.data()+3, 4);
		qDebug()<<"receive int:"<<value;
		//qDebug()<<value;
	}
    }
}
/*!\func processPendingDatagrams
 * обработчик событи€ "послать данные в сокет"
 * \param
 * - data - посылаемые данные
 * - host -адрес устройства
 * - port - удаленный порт
 * \return нет
 */
void TCore::sendDatagram(const QHostAddress &host, const quint16 &port, QByteArray data) {
    //qDebug()<<"sendDatagram";
    udpSocket.writeDatagram(data,host, port);
}
//! подвинуть виджет
void TCore::moveWidget(qint8 id, qint8 type, qint16 x, qint16 y, qint16 w, qint16 h)
{
    QByteArray datagram, data(16,0);
    memcpy(data.data(), &id, 1);
    memcpy(data.data()+1, &type, 1);
    qint8 oper1 = MainWindow::KOORD;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, &x, 2);
    memcpy(data.data()+5, &y, 2);
    memcpy(data.data()+7, &w, 2);
    memcpy(data.data()+9, &h, 2);
    sendDatagram(address, remoutePort, data);
    //qDebug()<<"send";
}
bool TCore::label_and_move()
{
    const qint8 id = 0;
    static qint32 move = 0;
    if(++move > 100)move = 0;
    moveWidget(id, LABEL, move*10, 100, 100, 30);
    QByteArray datagram, data(14,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LABEL;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::VALUE;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, "Hello, word!", 11);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::labelF()
{
    const qint8 id = 1;
    static float value = 13.5;
    value += 0.1;
    moveWidget(id, LABELF, 10, 200, 100, 30);
    QByteArray datagram, data(7,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LABELF;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::VALUE;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, &value, 4);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::labelI_and_hide()
{
    const qint8 id = 2;
    static qint32 value = 0;
    value++;
    moveWidget(id, LABELI, 10, 300, 100, 30);
    QByteArray datagram, data(14,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LABELI;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::VALUE;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, &value, 4);
    sendDatagram(address, remoutePort, data);
    if(value % 4)
    {
	QByteArray datagram, data(7,0);
	//show/hide
	oper1 = id;
	memcpy(data.data(), &oper1, 1);
	oper1 = LABELI;
	memcpy(data.data()+1, &oper1, 1);
	oper1 = SHOW;
	memcpy(data.data()+2, &oper1, 1);
	oper1 = 2;//hide
	memcpy(data.data()+3, &oper1, 4);
	sendDatagram(address, remoutePort, data);
    }
    return true;
}
bool TCore::list()
{
	enum ControlSymbols {
		I = 0x01,
		F,//0x02
		HEX,//0x03
	};
    const qint8 id = 3;
    QByteArray data(56,0);
    qint8 oper1 = id;
    moveWidget(id, LIST, 200, 10, 200, 300);
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LIST;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::VALUE;
    memcpy(data.data()+2, &oper1, 1);
    qint32 value1 = 13;
    oper1 = I;
    memcpy(data.data()+3, &oper1, 1);
    memcpy(data.data()+4, &value1, 4);
    memcpy(data.data()+8, "th pickaninny toward to sea...; ", 32);
    float valueF = 3.14;
    oper1 = F;
    memcpy(data.data()+40, &oper1, 1);
    memcpy(data.data()+41, &valueF, 4);
    memcpy(data.data()+45, " - pi.", 6);
    oper1 = HEX;
    memcpy(data.data()+51, &oper1, 1);
    value1 = 21;
    memcpy(data.data()+52, &value1, 4);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::enterF()
{
    const qint8 id = 4;
    static bool go = true;
    if(go)
    {
	moveWidget(id, ENTER_FLOAT, 500, 400, 80, 40);
	//go = false;
    }
    return true;
}
bool TCore::graph()
{
    enum CommandTypes {
	ADD_KOORD = 0,
	SETXTITLE,
	SETYTITLE,
    };
    //graphbody set val
    const qint8 id = 5;
    static float t = 0;
    if(!t)
	moveWidget(id, GRAPH, 460, 300, 300, 300);
    t += 0.1;
    QByteArray data(12,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = GRAPH;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = VALUE;
    memcpy(data.data()+2, &oper1, 1);
    static qint32 value = 0;
    oper1 = ADD_KOORD;
    memcpy(data.data()+3, &oper1, 1);
    value = 10*t*cos(t);
    memcpy(data.data()+4, &value, 4);
    value = 10*t*sin(t);
    memcpy(data.data()+8, &value, 4);
    /*value = t;
    memcpy(data.data()+12, &value, 4);
    value = cos(t);
    memcpy(data.data()+16, &value, 4);*/
    sendDatagram(address, remoutePort, data);
    //graphbody set title
    data.resize(12);
    oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = GRAPH;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = VALUE;
    memcpy(data.data()+2, &oper1, 1);
    qint8 oper2 = SETXTITLE;
    memcpy(data.data()+3, &oper2, 1);
    memcpy(data.data()+4, "x values", 8);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::led()
{
    enum ControlSymbols {
	    NAME = 0x00,
	    STATE,//0x01
    };
    enum States {
	    OFF = 0x00,
	    OK,//0x01
	    WARNING,//0x02
	    ALARM,//0x03
    };
    const qint8 id = 6;
    static qint8 value = 0;
    moveWidget(id, LED, 600, 100, 100, 30);
    QByteArray datagram, data(17,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = LED;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = VALUE;
    memcpy(data.data()+2, &oper1, 1);
    oper1 = NAME;
    memcpy(data.data()+3, &oper1, 1);
    memcpy(data.data()+4, "state of word", 13);
    sendDatagram(address, remoutePort, data);

    data.resize(5);
    oper1 = STATE;
    memcpy(data.data()+3, &oper1, 1);
    memcpy(data.data()+4, &value, 1);
    sendDatagram(address, remoutePort, data);
    if(++value > 0x03)value = 0;
    return true;
}
bool TCore::dial()
{
    const qint8 id = 7;
    static qint32 value = 0;
    moveWidget(id, ANALOG_DIAL, 500, 500, 100, 100);
    QByteArray datagram, data(7,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = ANALOG_DIAL;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = VALUE;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, &value, 4);
    sendDatagram(address, remoutePort, data);
    if(++value > 100)value = 0;
    return true;
}
bool TCore::dock()
{
	enum ControlSymbols {
		ADD_ITEM = 0,
		SET_TITLE,
	};
    const qint8 id = 8;
    moveWidget(id, DOCK, 700, 20, 300, 300);
    QByteArray datagram, data(9,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = DOCK;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = VALUE;
    memcpy(data.data()+2, &oper1, 1);
    oper1 = SET_TITLE;
    memcpy(data.data()+3, &oper1, 1);
    memcpy(data.data()+4, "title", 5);
    sendDatagram(address, remoutePort, data);
    data.resize(7);
    oper1 = ADD_ITEM;
    memcpy(data.data()+3, &oper1, 1);
    oper1 = 1;
    memcpy(data.data()+4, &oper1, 1);
    oper1 = 6;
    memcpy(data.data()+5, &oper1, 1);
    oper1 = 3;
    memcpy(data.data()+6, &oper1, 1);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::lcd_label()
{
	enum ControlSymbols {
		I = 0x01,
		F,//0x02
		HEX,//0x03
	};
    const qint8 id = 9;
    QByteArray data(7,0);
    qint8 oper1 = id;
    moveWidget(id, LCD_LABEL, 10, 500, 200, 100);
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LCD_LABEL;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::VALUE;
    memcpy(data.data()+2, &oper1, 1);
    static float value = 13.4;
    value += 0.4;
    memcpy(data.data()+3, &value, 4);
    sendDatagram(address, remoutePort, data);
    return true;
}
bool TCore::enterI()
{
    const qint8 id = 10;
    static bool go = true;
    if(go)
    {
	moveWidget(id, ENTER_INT, 600, 400, 80, 40);
	//go = false;
    }
    return true;
}
bool TCore::window_title()
{
    const qint8 id = 9;
    QByteArray data(12,0);
    qint8 oper1 = id;
    memcpy(data.data(), &oper1, 1);
    oper1 = MainWindow::LCD_LABEL;
    memcpy(data.data()+1, &oper1, 1);
    oper1 = MainWindow::SET_TITLE;
    memcpy(data.data()+2, &oper1, 1);
    memcpy(data.data()+3, "new title", 9);
    sendDatagram(address, remoutePort, data);
    return true;
}
