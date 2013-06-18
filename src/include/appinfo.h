#ifndef APPINFO_H
#define APPINFO_H
#include <QString>
#include <QPixmap>
class AppInfo
{
public:
    AppInfo();

    void setId(int id);
    void setName(QString name);
    void setPic(QString pic);
    void setSize(double size);
    void setLevel(int level);
    void setSummary(QString summary);
    void setDetail(QString detail);
    void setCategory(int category);

    int     getId();
    QString getName();
    QPixmap getPic();
    double  getSize();
    int     getLevel();
    QString getSummary();
    QString getDetail();
    int     getCategory();

private:
    int     id;
    QString name;
    QPixmap pic;
    double  size;
    int     level;
    QString summary;
    QString detail;
    int     category;


};

#endif // APPINFO_H
