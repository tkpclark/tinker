#ifndef APPLIST_H
#define APPLIST_H
#include "appinfo.h"
#include <QList>
class AppList
{
public:
    AppList();
    QList<AppInfo *> fetchApplist(int category);
private:
    QList<AppInfo> applist;
};

#endif // APPLIST_H
