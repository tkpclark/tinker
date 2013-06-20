#ifndef APPLIST_H
#define APPLIST_H
#include "src/include/appinfo.h"
#include <QList>

typedef struct InstallationResult
{
    bool    success;
    QString message;

}InstallationResult;


class AppList
{
public:
    AppList();
    QList<AppInfo *> fetchApplist(int category);
    QList<InstallationResult *> installApplist(QList<AppInfo *>);
    InstallationResult installOneApp(AppInfo *);
    bool loadXMLData(QString &);

private:
    QList<AppInfo> applist;
    QList<InstallationResult> installationResultList;
};

#endif // APPLIST_H
