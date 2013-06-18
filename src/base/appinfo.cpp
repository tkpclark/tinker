#include "src/include/appinfo.h"

AppInfo::AppInfo()
{
}

//set
void AppInfo::setId(int id)
{
    this->id=id;
}
void AppInfo::setName(QString name)
{
    this->name=name;
}

void AppInfo::setPic(QString pic)
{
    QPixmap pixmap(pic);
    this->pic=pixmap;
}
void AppInfo::setCategory(int category)
{
    this->category=category;
}
void AppInfo::setSize(double size)
{
    this->size=size;
}

void AppInfo::setLevel(int level)
{
    this->level=level;
}

void AppInfo::setSummary(QString summary)
{
    this->summary=summary;
}

void AppInfo::setDetail(QString detail)
{
    this->detail=detail;
}

//get
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

int AppInfo::getCategory()
{
    return this->category;
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
