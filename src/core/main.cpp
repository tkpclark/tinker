#include <QApplication>
#include "src/include/tinkermainwindow.h"

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    TinkerMainWindow *win = new TinkerMainWindow;
    win->show();
    return app.exec();
}



