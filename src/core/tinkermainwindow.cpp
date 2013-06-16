#include "src/include/tinkermainwindow.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QRegExp>

TinkerMainWindow::TinkerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    this->initEnv();
    this->initMainWindow();
    this->initOtherWidgets();
}

void TinkerMainWindow::initEnv()
{
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
}

void TinkerMainWindow::initMainWindow()
{
    this->setStyleSheet("background-color: black;");
    int x = this->width()/4;
    int y =this->height()/8;
    this->setContentsMargins(x,y,x,y);
    this->showFullScreen();
    this->resize(800, 480);
}

void TinkerMainWindow::initOtherWidgets()
{
    QWidget *centralWidget = this->centralWidget();
    centralWidget->setStyleSheet("background:rgb(101,211,255);border-radius: 10px;");
    int x = centralWidget->width()/8;
    int y = centralWidget->height()/8;
    centralWidget->setContentsMargins(x,y,x,y);
    this->logoLabel->setStyleSheet("color:white");
    this->userNameWidget->setStyleSheet("background:white;border-radius: 20px;");
    this->userNameLabel->setStyleSheet("color:rgb(101,211,255);font:bold;");
    this->userNameLineEdit->setFixedWidth(128);
    this->passwordWidget->setStyleSheet("background:white;border-radius: 20px;");
    this->passwordLabel->setStyleSheet("color:rgb(101,211,255);font:bold;");
    this->passwordLineEdit->setFixedWidth(128);
    this->loginWidget->setStyleSheet("background:rgb(43,146,2);border-radius: 20px;");
    this->loginPushButton->setStyleSheet("color:white;font:bold;");
}

void TinkerMainWindow::on_loginPushButton_clicked()
{
    if(this->userNameLineEdit->text() == "Vasilis" &&
       this->passwordLineEdit->text() == "123") {
        this->centralWidget()->deleteLater();
//        this->hide();
        QMessageBox msgBox;
        msgBox.setText(tr("×ßÄã"));
        msgBox.exec();
    }
}
