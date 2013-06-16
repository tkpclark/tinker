#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"

#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>

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
    this->timeLabel->setStyleSheet("color:rgb(128,128,128)");
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(60000);
    TinkerMainWindow *tk = dynamic_cast<TinkerMainWindow*>(this->parent());
    if(tk->getUserName().isEmpty())
    {
        this->userNamelabel->setText("USER008");
    }
    else
    {
        this->userNamelabel->setText(tk->getUserName());
    }
    this->userNamelabel->setStyleSheet("color:rgb(128,128,128)");
    this->exitPushButton->setStyleSheet("color:rgb(128,128,128);background:rgb(55,55,55);");
    this->appListWidget->setStyleSheet("background-color: rgb(47,47,47);");
    this->pageWidget->setStyleSheet("background-color: rgb(38,38,38);");
    this->userChoiceWidget->setStyleSheet("background-color: rgb(25,117,0);");
    this->indispensableWidget->setStyleSheet("background-color: rgb(69,181,255);");
    this->fineGameWidget->setStyleSheet("background-color: rgb(255,127,0);");
    this->newAppWidget->setStyleSheet("background-color: rgb(248,0,74);");
    this->recommendWidget->setStyleSheet("background-color: rgb(203,203,203);");

    this->installPushButton->setStyleSheet("background-color: rgb(46,150,2);color:white;");
    this->listWidget->setStyleSheet("border-style: solid;border-color:red;");

    // navigationWidget
    this->userChoiceLabel->setStyleSheet("color: white;");
    this->indispensableLabel->setStyleSheet("color: white;");
    this->fineGameLabel->setStyleSheet("color: white;");
    this->newAppLabel->setStyleSheet("color: white;");
    this->recommendLabel->setStyleSheet("color: rgb(55,55,55);");



    // appWidget1
    this->appWidget1->setStyleSheet("background-color: rgb(223,223,223);");
    this->appSelectionFrame1->setStyleSheet("background-color: rgb(221,221,221);border-radius: 6px;border: 1px; border-color: rgb(200,200,200);border-style : outset;");
    this->appSelectionPushButton1->setStyleSheet("border: 1px;text-align : right;");
    this->appCrossPicLabel1->setStyleSheet("border: 0px;");

    // choosedWidget
    this->choosedWidget->setStyleSheet("background-color: rgb(197,197,197);");

}

void InstallationWidget::updateTime()
{
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm ap"));
}

void InstallationWidget::on_exitPushButton_clicked()
{
    QCoreApplication::exit();
}
