#include "src/include/tinkermainwindow.h"
#include "src/include/installationwidget.h"
#include <QMessageBox>
#include <QRegExp>
#include <QTextCodec>

TinkerMainWindow::TinkerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    this->setWindowTitle("Tinker");
    this->initMainWindow();
    this->initOtherWidgets();
    this->initEnv();
}
void TinkerMainWindow::initEnv()
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
}


void TinkerMainWindow::initMainWindow()
{
    int x = this->width()/4;
    int y =this->height()/8;
    this->setContentsMargins(x,y,x,y);
    //this->showFullScreen();

    setWindowFlags(Qt::FramelessWindowHint);
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
