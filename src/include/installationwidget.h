#ifndef INSTALLATIONWIDGET_H
#define INSTALLATIONWIDGET_H
#include "ui_installation.h"

#include <QWidget>

class InstallationWidget : public QWidget, public Ui::InstallationWidget
{
    Q_OBJECT
public:
    explicit InstallationWidget(QWidget *parent = 0);
    void initOtherWidgets();
    void updateTime();

signals:

public slots:
    void on_exitPushButton_clicked();
};

#endif // INSTALLATIONWIDGET_H
