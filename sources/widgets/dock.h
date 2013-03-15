#ifndef DOCK_H
#define DOCK_H
#include <widget.h>
#include <QVBoxLayout>

class MainWindow;

class Dock : public Widget
{
public:
	enum ControlSymbols {
		ADD_ITEM = 0,
		SET_TITLE,
	};

    Dock(MainWindow* mw, Log*log);
    ~Dock();
    virtual void setValue(const QByteArray& data);
private:
    MainWindow* mw;
    QVBoxLayout *layout;
};

#endif // DOCK_H
