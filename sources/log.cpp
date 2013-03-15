#include <QToolBar>
#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Log)
{
    m_ui->setupUi(this);
    m_ui->plainTextEdit->setReadOnly(true);
    QToolBar *bar = new QToolBar("", this);
    bar->addAction(m_ui->actionAClear);
    m_ui->verticalLayout->insertWidget(0, bar);

}

Log::~Log()
{
    delete m_ui;
}

void Log::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
//! добавить сообщение в лог
void Log::addMsg(const QString&msg)
{
    m_ui->plainTextEdit->appendPlainText(msg);
}
//! враги пытаются закрыть форму
void Log::closeEvent ( QCloseEvent * event )
{
    hide();
    event->ignore();
}
//очистить лог
void Log::on_actionAClear_triggered()
{
    m_ui->plainTextEdit->clear();
}
