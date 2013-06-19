#ifndef LINUXCOMMAND_H
#define LINUXCOMMAND_H

#include <QString>

class LinuxCommand
{
public:
    LinuxCommand();
    QString execute(QString &command);
};

#endif // LINUXCOMMAND_H
