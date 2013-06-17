#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"

#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>

InstallationWidget::InstallationWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    this->initOtherWidgets();

}

void InstallationWidget::initOtherWidgets()
{
    // init time display
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(60000);    // update every 1 min

    // display user name
    TinkerMainWindow *tk = dynamic_cast<TinkerMainWindow*>(this->parent());
    if(tk->getUserName().isEmpty())
    {
        this->userNameWordLabel->setText("USER008");
    }
    else
    {
        this->userNameWordLabel->setText(tk->getUserName());
    }

}

void InstallationWidget::updateTime()
{
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm ap"));
}

void InstallationWidget::on_exitPushButton_clicked()
{
    QCoreApplication::exit();
}
