#include <QApplication>
#include <QFile>
#include "src/include/tinkermainwindow.h"

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QFile file(":/qss/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString StyleSheet = QLatin1String(file.readAll());
       app.setStyleSheet(StyleSheet);
    }
    TinkerMainWindow *win = new TinkerMainWindow;
    win->show();
    return app.exec();
}



