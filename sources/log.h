#ifndef LOG_H
#define LOG_H

#include <QtGui/QWidget>

namespace Ui {
    class Log;
}

class Log : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Log)
public:
    explicit Log(QWidget *parent = 0);
    virtual ~Log();
    void addMsg(const QString&msg);

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent ( QCloseEvent * event );
private:
    Ui::Log *m_ui;

private slots:
    void on_actionAClear_triggered();
};

#endif // LOG_H
