#include "src/include/tinkertest.h"
#include "src/include/applist.h"
#include "src/include/appinfo.h"
#include "src/include/linuxcommand.h"
#include <QDebug>

void testAll()
{
    testAppList_fetchApplist();
    //testAppList_installApplist();
    //testAppList_loadXMLData();
    //testLinuxCommand();
}

void testAppList_fetchApplist()
{

    /*--------test fetchApplist--------*/

    AppList appList;

    QList<AppInfo *> apppointerlist;

    apppointerlist = appList.fetchApplist(3);

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
void testAppList_installApplist()
{

    /*--------test installApplist--------*/

    AppList appList;

    QList<AppInfo *> apppointerlist;
    apppointerlist = appList.fetchApplist(2);

    //define a InstallationResultList to save the return value of installApplist
    QList<InstallationResult *> list;
    list = appList.installApplist(apppointerlist);

    QList<InstallationResult *>::iterator it1;
    qDebug() << "result count: " << list.size();

    InstallationResult *installationresult;
    for(it1 = list.begin(); it1 != list.end(); ++it1)
    {
        installationresult = *it1;
        qDebug() << installationresult->success << ", " << installationresult->message;
    }

}


void testAppList_loadXMLData()
{
    AppList appList;
    //QString xmlFileName = "/Users/clark/tmp/test.xml";
    //appList.loadXMLData(xmlFileName);
}

void testLinuxCommand()
{
    LinuxCommand linuxCommand;
    QString command = "ifconfig";
    linuxCommand.execute(command);
}
