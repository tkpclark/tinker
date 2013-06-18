#include <QApplication>
#include <QFile>
#include "src/include/tinkermainwindow.h"
#include "src/include/tinkertest.h"
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QFile file(":/qss/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString styleSheet = QLatin1String(file.readAll());
       app.setStyleSheet(styleSheet);
       file.close();
    }
    TinkerMainWindow *win = new TinkerMainWindow;
    win->show();

    testAppList();
    return app.exec();
}



