#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"

#include <QTimer>
#include <QDateTime>

InstallationWidget::InstallationWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    this->setStyleSheet("background:black;");
    this->initOtherWidgets();

}

void InstallationWidget::initOtherWidgets()
{
    this->logoLabel->setStyleSheet("color:white;font:bold;");
//    this->timeLabel->setStyleSheet("color:rgb(128,128,128)");
    this->timeLcdNumber->setStyleSheet("color:white;background:red;");
    this->timeLcdNumber->display(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);
    TinkerMainWindow *tk = dynamic_cast<TinkerMainWindow*>(this->parent());
    this->userNamelabel->setText(tk->getUserName());
    this->userNamelabel->setStyleSheet("color:red");
}

void InstallationWidget::updateTime()
{
    this->timeLcdNumber->display(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
