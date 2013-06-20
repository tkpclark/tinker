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
    void setApkPath(const QString &apkPath);
    void setPackageName(const QString &packageName);
    void setCategory(QString category);


    int     getId();
    QString getName();
    QPixmap getPic();
    double  getSize();
    int     getLevel();
    QString getSummary();
    QString getDetail();
    QString getApkPath();
    QString getPackageName();
    QString getCategory();

private:
    int     id;
    QString name;
    QPixmap pic;
    double  size;
    int     level;
    QString summary;
    QString detail;
    QString apkPath;
    QString packageName;
    QString category;

};

#endif // APPINFO_H
