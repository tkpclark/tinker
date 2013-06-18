#include "src/include/tinkertest.h"
#include "src/include/applist.h"
#include "src/include/appinfo.h"
#include <QDebug>


void testAppList()
{
    AppList appList;
    QList<AppInfo *> apppointerlist;

    apppointerlist = appList.fetchApplist(2);

    QList<AppInfo *>::iterator it;

    for(it = apppointerlist.begin(); it != apppointerlist.end(); ++it)
    {
        AppInfo *app = *it;
        qDebug() << app->getId()          \
                 << app->getName()        \
                 << app->getSize()        \
                 << app->getSummary()     \
                 << app->getDetail()      \
                 << app->getLevel()       \
                 << app->getPic().size();

    }

    qDebug() << "list size: " << apppointerlist.size();
}
