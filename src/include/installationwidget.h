#ifndef INSTALLATIONWIDGET_H
#define INSTALLATIONWIDGET_H
#include "ui_installation.h"

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>

#define TYPE_USER_CHOICE 0
#define TYPE_INDISPENSABLE 1
#define TYPE_FINE_GAME 2
#define TYPE_NEW_APP 3
#define TYPE_RECOMMEND 4

class ChoosedOption
{
public:
    explicit ChoosedOption(QPushButton *pushButton, QLabel *tickLabel);
    QPushButton *pushButton;
    QLabel *tickLabel;
};

class InstallationWidget : public QWidget, public Ui::InstallationWidget
{
    Q_OBJECT
public:
    explicit InstallationWidget(QWidget *parent = 0);
    void initOtherWidgets();
    void getTickPixmap();
    void displayAppList(int type, QPushButton *pushButton, QLabel *tickLabel);

signals:

public slots:
    void on_exitPushButton_clicked();
    void on_userChoicePushButton_clicked();
    void on_indispensablePushButton_clicked();
    void on_fineGamePushButton_clicked();
    void on_newAppPushButton_clicked();
    void on_recommendPushButton_clicked();
    void updateTime();

private:
    QPixmap tickPixmap;
    ChoosedOption *currentChoosedOption;

};

#endif // INSTALLATIONWIDGET_H
