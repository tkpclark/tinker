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

signals:

public slots:
    void updateTime();
};

#endif // INSTALLATIONWIDGET_H
