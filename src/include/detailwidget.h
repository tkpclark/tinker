#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include "ui_detail.h"
#include "src/include/appinfo.h"
#include "src/include/installationwidget.h"

#include <QWidget>

class DetailWidget : public QWidget, public Ui::DetailWidget
{
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = 0);
    void displayAppDetail(AppInfo *appInfo);

signals:

public slots:
    void on_backPushButton_clicked();


private:
    InstallationWidget *parent;
};

#endif // DETAILWIDGET_H
