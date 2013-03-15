#ifndef CORE_H
#define CORE_H
#include <QTimer>
#include <QWidget>
#include <QtNetwork/QUdpSocket>
/* Core
   класс-ядро, загружает плагины,
   отвечает за передачу данных,
   за прием команд и их перенаправление,
   хранит список доступных устройств,
   загружает конфиги
 */
class TCore: QObject {
    Q_OBJECT
private:
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
    int unique_id;
    quint16 localPort;
    quint16 remoutePort;
    QString pluginsDir;
    QUdpSocket udpSocket;//соккет для общения с платой
    QHostAddress address;
    QTimer timer;
public:
    TCore(const QString &newPluginsDir, quint16 localPort);//конструктор
    ~TCore();//деструктор
private slots:
    void on_timer();
    void moveWidget(qint8 id, qint8 type, qint16 x, qint16 y, qint16 w, qint16 h);
    void processPendingDatagrams();
    void sendDatagram(const QHostAddress &host, const quint16 &port, QByteArray data);
private://tests
    bool label_and_move();
    bool labelF();
    bool labelI_and_hide();
    bool list();
    bool window_title();
    bool enterF();
    bool enterI();
    bool graph();
    bool led();
    bool dial();
    bool dock();
    bool lcd_label();
};
#endif // CORE_H
