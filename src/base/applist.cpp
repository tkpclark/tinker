#include "src/include/applist.h"
#include <QDebug>

AppList::AppList()
{
    AppInfo appInfo;


    QString name = "taobao";
    QString summary = "this is summary";
    QString detail = "this is deatail";
    QString picpath = "/path/pic/name";
    QString apkpath = "/path/apk/name";

    appInfo.setId(1);
    appInfo.setCategory(1);
    appInfo.setName(name);
    appInfo.setLevel(4);
    appInfo.setDetail(detail);
    appInfo.setPic(picpath);
    appInfo.setSize(1.54);
    appInfo.setSummary(summary);
    appInfo.setApkPath(apkpath);
    this->applist.append(appInfo);

    appInfo.setId(2);
    appInfo.setCategory(1);
    appInfo.setName(name);
    appInfo.setLevel(5);
    appInfo.setDetail(detail);
    appInfo.setPic(picpath);
    appInfo.setSize(2.43);
    appInfo.setSummary(summary);
    appInfo.setApkPath(apkpath);
    this->applist.append(appInfo);

    appInfo.setId(3);
    appInfo.setCategory(2);
    appInfo.setName(name);
    appInfo.setLevel(5);
    appInfo.setDetail(detail);
    appInfo.setPic(picpath);
    appInfo.setSize(2.43);
    appInfo.setSummary(summary);
    appInfo.setApkPath(apkpath);
    this->applist.append(appInfo);

    appInfo.setId(4);
    appInfo.setCategory(2);
    appInfo.setName(name);
    appInfo.setLevel(5);
    appInfo.setDetail(detail);
    appInfo.setPic(picpath);
    appInfo.setSize(2.43);
    appInfo.setSummary(summary);
    appInfo.setApkPath(apkpath);
    this->applist.append(appInfo);

    /*
    QList<AppInfo *>::iterator it;
    for(it = applist.begin(); it != applist.end(); ++it)
    {
        qDebug() << (*it)->getId() << " " << (*it)->getName();
    }
    */
}
//to get a list of certain category
QList<AppInfo *> AppList::fetchApplist(int category)
{
    QList<AppInfo *> apppointerlist;
    QList<AppInfo>::iterator it;
    for(it = this->applist.begin(); it != this->applist.end(); ++it)
    {
        if( (*it).getCategory() == category)
            apppointerlist.append(&(*it));
    }
    return apppointerlist;
}

InstallationResult AppList::installOneApp(QString apkPath)
{
    InstallationResult installationResult;

    installationResult.success = true;
    installationResult.message = "success";

    return installationResult;
}

//
QList<InstallationResult *> AppList::installApplist(QList<AppInfo *> applist)
{

    //just to be on the safe side
    installationResultList.clear();

    ///////install the app in the list one by one
    QList<AppInfo *>::iterator it;

    //for return
    QList<InstallationResult *> returnlist;

    qDebug() << "install list:";

    InstallationResult installationResult;

    for(it = applist.begin(); it != applist.end(); ++it)
    {
        qDebug() << (*it)->getApkPath();

        installationResult = installOneApp((*it)->getApkPath());

        installationResultList.append(installationResult);
        returnlist.append(&installationResultList.last());


    }


    return returnlist;
}
