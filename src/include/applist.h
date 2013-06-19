#ifndef APPLIST_H
#define APPLIST_H
#include "appinfo.h"
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

private:
    QList<AppInfo> applist;
    InstallationResult installOneApp(QString apkPath);
    QList<InstallationResult> installationResultList;
};

#endif // APPLIST_H
