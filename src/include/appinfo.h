#ifndef APPINFO_H
#define APPINFO_H
#include <QString>
#include <QPixmap>
class AppInfo
{
public:
    AppInfo();

    void setId(int id);
    void setName(const QString &name);
    void setPic(const QString &pic);
    void setSize(double size);
    void setLevel(int level);
    void setSummary(const QString &summary);
    void setDetail(const QString &detail);
    void setCategory(int category);
    void setApkPath(const QString &apkPath);

    int     getId();
    QString getName();
    QPixmap getPic();
    double  getSize();
    int     getLevel();
    QString getSummary();
    QString getDetail();
    int     getCategory();
    QString getApkPath();

private:
    int     id;
    QString name;
    QPixmap pic;
    double  size;
    int     level;
    QString summary;
    QString detail;
    int     category;
    QString apkPath;


};

#endif // APPINFO_H
