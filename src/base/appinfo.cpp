#include "src/include/appinfo.h"

AppInfo::AppInfo()
{
}

//////////////get///////////////
void AppInfo::setId(int id)
{
    this->id=id;
}
void AppInfo::setName(const QString &name)
{
    this->name=name;
}

void AppInfo::setPic(const QString &pic)
{
    QPixmap pixmap(pic);
    this->pic=pixmap;
}

void AppInfo::setSize(double size)
{
    this->size=size;
}

void AppInfo::setLevel(int level)
{
    this->level=level;
}

void AppInfo::setSummary(const QString &summary)
{
    this->summary=summary;
}

void AppInfo::setDetail(const QString &detail)
{
    this->detail=detail;
}

void AppInfo::setApkPath(const QString &apkPath)
{
    this->apkPath=apkPath;
}

void AppInfo::setPackageName(const QString &packageName)
{
    this->packageName=packageName;
}

void AppInfo::setCategory(QString category)
{
    this->category=category;
}


//////////////get///////////////
int AppInfo::getId()
{
    return this->id;
}

QString AppInfo::getName()
{
    return this->name;
}

QPixmap AppInfo::getPic()
{
    return this->pic;
}

double AppInfo::getSize()
{
    return this->size;
}

int AppInfo::getLevel()
{
    return this->level;
}

QString AppInfo::getSummary()
{
    return this->summary;
}

QString AppInfo::getDetail()
{
    return this->detail;
}

QString AppInfo::getApkPath()
{
    return this->apkPath;
}

QString AppInfo::getPackageName()
{
    return this->packageName;
}


QString AppInfo::getCategory()
{
    return this->category;
}

