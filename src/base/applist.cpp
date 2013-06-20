#include "src/include/applist.h"
#include "src/include/linuxcommand.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomNode>
#include <QDomNodeList>

AppList::AppList()
{
    /*
    AppInfo appInfo;


    QString name = "taobao";
    QString summary = "this is summary";
    QString detail = "this is deatail";
    QString picpath = "/path/pic/name";
    QString apkpath = "/path/apk/name";
    QString packageName = "package name";

    appInfo.setId(1);
    appInfo.setCategory(1);
    appInfo.setName(name);
    appInfo.setLevel(4);
    appInfo.setDetail(detail);
    appInfo.setPic(picpath);
    appInfo.setSize(1.54);
    appInfo.setSummary(summary);
    appInfo.setApkPath(apkpath);
    appInfo.setPackageName(packageName);
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
    appInfo.setPackageName(packageName);
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
    appInfo.setPackageName(packageName);
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
    appInfo.setPackageName(packageName);
    this->applist.append(appInfo);

    */
    /*
    QList<AppInfo *>::iterator it;
    for(it = applist.begin(); it != applist.end(); ++it)
    {
        qDebug() << (*it)->getId() << " " << (*it)->getName();
    }
    */

//    LinuxCommand linuxCommand;
//    QString command="ls ../../../../tinker/data";
//    linuxCommand.execute(command);
//    QString xmlFileName = "../../../../tinker/data/test.xml";
    QString xmlFileName("../tinker_git/data/test.xml");
    this->loadXMLData(xmlFileName);
}
//to get a list of certain category
bool AppList::loadXMLData(QString &xmlFileName)
{
    //char filename[]="/Users/clark/tmp/test.xml";

    qDebug() << "loading data from file: " << xmlFileName;
    QFile file(xmlFileName);
    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "open file " << xmlFileName << " failed"
                 << " error: " << file.errorString();
        return false;
    }


    QDomDocument    document;

    QString         strError;
    int             errLin = 0, errCol = 0;

    //////

    if( !document.setContent(&file, false, &strError, &errLin, &errCol) ) {
        qDebug() << "parse file failed at line "<< errLin << "column" << errCol
                 << "error" << strError ;
        return false;
    }

    if( document.isNull() ) {
        qDebug() << "document is null !";
        return false;
    }

    qDebug() << "begin to parse...";
    QDomElement root = document.documentElement();
 // qDebug() << root.tagName();
 // qDebug() << root.text();


    QDomNodeList appList = root.childNodes();
//  qDebug() << appinfo.tagName() << " " << appinfo.text();


    for(int i = 0; i < appList.count(); i++)
    {
        QDomNodeList appInfo  = appList.at(i).childNodes();
        AppInfo tmpAppInfo;

        for(int j = 0; j < appInfo.count(); j++)
        {
            QDomElement appAttr = appInfo.at(j).toElement();

           // qDebug() << appAttr.tagName() << " " << appAttr.text();



            if(!appAttr.tagName().compare("Id"))
            {
                tmpAppInfo.setId(appAttr.text().toInt());
            }
            if(!appAttr.tagName().compare("Name"))
            {
                tmpAppInfo.setName(appAttr.text());
            }
            if(!appAttr.tagName().compare("Level"))
            {
                tmpAppInfo.setLevel(appAttr.text().toInt());
            }
            if(!appAttr.tagName().compare("Size"))
            {
                tmpAppInfo.setSize(appAttr.text().toDouble());
            }
            if(!appAttr.tagName().compare("Summary"))
            {
                tmpAppInfo.setSummary(appAttr.text());
            }
            if(!appAttr.tagName().compare("Detail"))
            {
                tmpAppInfo.setDetail(appAttr.text());
            }
            if(!appAttr.tagName().compare("PicPath"))
            {
                tmpAppInfo.setPic(appAttr.text());
            }
            if(!appAttr.tagName().compare("ApkPath"))
            {
                tmpAppInfo.setApkPath(appAttr.text());
            }
            if(!appAttr.tagName().compare("PackageName"))
            {
                tmpAppInfo.setPackageName(appAttr.text());
            }
            if(!appAttr.tagName().compare("Category"))
            {
                tmpAppInfo.setCategory(appAttr.text());
            }



        }

        qDebug() << tmpAppInfo.getId();
        qDebug() << tmpAppInfo.getName();
        qDebug() << tmpAppInfo.getApkPath();
        qDebug() << tmpAppInfo.getDetail();
        qDebug() << tmpAppInfo.getLevel();
        qDebug() << tmpAppInfo.getPackageName();
        qDebug() << tmpAppInfo.getPic().size();
        qDebug() << tmpAppInfo.getSize();
        qDebug() << tmpAppInfo.getSummary();
        qDebug() << tmpAppInfo.getCategory();


        this->applist.append(tmpAppInfo);

    }
    return true;

}

QList<AppInfo *> AppList::fetchApplist(int category)
{
    QString strCategory = QString::number(category,10);
    QList<AppInfo *> apppointerlist;
    QList<AppInfo>::iterator it;
    for(it = this->applist.begin(); it != this->applist.end(); ++it)
    {
        if( (*it).getCategory().indexOf(strCategory) >= 0)//include this category
            apppointerlist.append(&(*it));
    }
    return apppointerlist;
}

InstallationResult AppList::installOneApp(AppInfo * appinfo)
{
    LinuxCommand linuxCommand;
    QString command;


    command = "./adb shell pm path " + appinfo->getPackageName();
    linuxCommand.execute(command);


    command = "./adb install -r " + appinfo->getApkPath();
    linuxCommand.execute(command);



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

        installationResult = installOneApp(*it);

        installationResultList.append(installationResult);
        returnlist.append(&installationResultList.last());


    }


    return returnlist;
}
