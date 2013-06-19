#include "src/include/linuxcommand.h"
#include <QDebug>

LinuxCommand::LinuxCommand()
{
}
QString LinuxCommand::execute(QString &command)
{


    char newCommand[1024];
    sprintf(newCommand, "%s  2>&1",(char *)command.toLatin1().data());

    qDebug() << "excute command:\n" << newCommand;


    //excute
    FILE *fp;
    if((fp = popen(newCommand,"r")) == NULL)
    {
        //printscreen("ERR:Fail to execute:%s\n",cmd);
        qDebug() <<"ERR:Fail to execute:\n" << newCommand;
        return "failed";
    }


    //read output
    char buffer[512];
    QString commandOutput;

    while(fgets(buffer, sizeof(buffer)-1, fp) != NULL)
    {
        commandOutput += buffer;
    }

    pclose(fp);

    qDebug() << "result:\n" << commandOutput;
    return commandOutput;
}
