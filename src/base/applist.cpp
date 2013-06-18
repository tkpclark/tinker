#include "src/include/applist.h"
#include <QDebug>

AppList::AppList()
{
    AppInfo appInfo;

    appInfo.setId(1);
    appInfo.setCategory(1);
    appInfo.setName("taobao");
    appInfo.setLevel(4);
    appInfo.setDetail("this is detail of the app");
    appInfo.setPic("/path/aaa.pic");
    appInfo.setSize(1.54);
    appInfo.setSummary("this is summary of the app");
    this->applist.append(appInfo);

    appInfo.setId(2);
    appInfo.setCategory(1);
    appInfo.setName("qq");
    appInfo.setLevel(5);
    appInfo.setDetail("this is detail of the app");
    appInfo.setPic("/path/aaa.pic");
    appInfo.setSize(2.43);
    appInfo.setSummary("this is summary of the app");
    this->applist.append(appInfo);

    appInfo.setId(3);
    appInfo.setCategory(2);
    appInfo.setName("baidu");
    appInfo.setLevel(5);
    appInfo.setDetail("this is detail of the app");
    appInfo.setPic("/path/aaa.pic");
    appInfo.setSize(2.43);
    appInfo.setSummary("this is summary of the app");
    this->applist.append(appInfo);

    appInfo.setId(4);
    appInfo.setCategory(2);
    appInfo.setName("google");
    appInfo.setLevel(5);
    appInfo.setDetail("this is detail of the app");
    appInfo.setPic("/path/aaa.pic");
    appInfo.setSize(2.43);
    appInfo.setSummary("this is summary of the app");
    this->applist.append(appInfo);

    /*
    QList<AppInfo *>::iterator it;
    for(it = applist.begin(); it != applist.end(); ++it)
    {
        qDebug() << (*it)->getId() << " " << (*it)->getName();
    }
    */
}
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
