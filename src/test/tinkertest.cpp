#include "src/include/tinkertest.h"
#include "src/include/applist.h"
#include "src/include/appinfo.h"
#include <QDebug>


void testAppList()
{
    AppList appList;


    //test fetchApplist

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



    //test installApplist
    QList<InstallationResult *> list;
    list = appList.installApplist(apppointerlist);

    QList<InstallationResult *>::iterator it1;
    qDebug() << "result count: " << list.size();
    for(it1 = list.begin(); it1 != list.end(); ++it1)
    {
        qDebug() << (*it1)->success;// << " " << (*it1)->message;
    }

}
