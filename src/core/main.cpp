#include <QApplication>
#include <QFile>
#include "src/include/tinkermainwindow.h"
#include "src/include/tinkertest.h"
#include <QWSServer>
#include <QFileInfo>
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    QFileInfo fi("/linuxrc");
    //QWSServer::setCursorVisible(false);
    QFile file(":/qss/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString styleSheet = QLatin1String(file.readAll());
       app.setStyleSheet(styleSheet);
       file.close();
    }
    TinkerMainWindow *win = new TinkerMainWindow;
    win->show();

//    testAll();
    return app.exec();
}



