#include "src/include/tinkertest.h"
#include "src/include/applist.h"
#include <QDebug>
void testAppList()
{
    AppList appList;
    QList<AppInfo *> apppointerlist;

    apppointerlist = appList.fetchApplist(2);

    QList<AppInfo *>::iterator it;

    for(it = apppointerlist.begin(); it != apppointerlist.end(); ++it)
    {
        qDebug() << (*it)->getId()          \
                 << (*it)->getName()        \
                 << (*it)->getSize()        \
                 << (*it)->getSummary()     \
                 << (*it)->getDetail()      \
                 << (*it)->getLevel()       \
                 << (*it)->getPic();

    }

    qDebug() << "list size: " << apppointerlist.size();
}
