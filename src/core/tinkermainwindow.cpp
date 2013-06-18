#include "src/include/tinkermainwindow.h"
#include "src/include/installationwidget.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QRegExp>

TinkerMainWindow::TinkerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    this->initMainWindow();
    this->initOtherWidgets();
}

void TinkerMainWindow::initMainWindow()
{
    int x = this->width()/4;
    int y =this->height()/8;
    this->setContentsMargins(x,y,x,y);
//    this->showFullScreen();
    this->resize(800, 480);
}

void TinkerMainWindow::initOtherWidgets()
{
    QWidget *centralWidget = this->centralWidget();
    int x = centralWidget->width()/8;
    int y = centralWidget->height()/8;
    centralWidget->setContentsMargins(x,y,x,y);

}

void TinkerMainWindow::on_loginPushButton_clicked()
{
    // TODO login validate
    this->userName = this->userNameLineEdit->text();
    this->centralWidget()->deleteLater();
    InstallationWidget *installationWidget = new InstallationWidget(this);
    this->setCentralWidget(installationWidget);
    this->setContentsMargins(0,0,0,0);
    installationWidget->show();
}

QString TinkerMainWindow::getUserName()
{
    return this->userName;
}
