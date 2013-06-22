#ifndef INSTALLATIONWIDGET_H
#define INSTALLATIONWIDGET_H
#include "ui_installation.h"
#include "src/include/applist.h"

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QSet>
#include <QIcon>

#define TYPE_USER_CHOICE 1
#define TYPE_INDISPENSABLE 2
#define TYPE_FINE_GAME 3
#define TYPE_NEW_APP 4
#define TYPE_RECOMMEND 5
#define PAGE_DEFAULT 1
#define SIZE_DEFAULT 9


class ChoosedOption
{
public:
    ChoosedOption(QPushButton *pushButton, QLabel *tickLabel);
    QPushButton *pushButton;
    QLabel *tickLabel;
};

class AppGrid
{
public:
    AppGrid(QFrame *appFrame, QLabel *appPicLabel, QLabel *appNameLabel, QLabel *appSizeContentLabel, QLabel *appLevelLabel, QWidget *appPicWordWidget, QFrame *appSelectionFrame, QPushButton *appSelectionPushButton, QLabel *appTickPicLabel, bool selected);
    QFrame *appFrame;
    QLabel *appPicLabel;
    QLabel *appNameLabel;
    QLabel *appSizeContentLabel;
    QLabel *appLevelLabel;
    QWidget *appPicWordWidget;
    QFrame *appSelectionFrame;
    QPushButton *appSelectionPushButton;
    QLabel *appTickPicLabel;
    bool selected;
    int appId;
    double appSize;
};

class ChoosedAppItem
{
public:
    ChoosedAppItem(QLabel *choosedAppDotLabel, QLabel *choosedAppNameLabel);
    QLabel *choosedAppDotLabel;
    QLabel *choosedAppNameLabel;
};

class InstallationWidget : public QWidget, public Ui::InstallationWidget
{
    Q_OBJECT
public:
    explicit InstallationWidget(QWidget *parent = 0);
    void getTickPixmap();
    void changeOptionButtonAndAppList(int type, QPushButton *pushButton, QLabel *tickLabel);
    void displayAppList(int type, int page, int size);
    void changeSelectionState(QPushButton *pushButton, QLabel *tickLabel, int position);
    void hideAllAppGrid();
    void addSelectedApp(int appId);
    void removeSelectedApp(int appId);
    void toSelectedState(QPushButton *appSelectionPushButton, QLabel *appTickPicLabel);
    void toCancelledState(QPushButton *appSelectionPushButton, QLabel *appTickPicLabel);

signals:

public slots:
    void updateTime();
    void on_exitPushButton_clicked();
    void on_userChoicePushButton_clicked();
    void on_indispensablePushButton_clicked();
    void on_fineGamePushButton_clicked();
    void on_newAppPushButton_clicked();
    void on_recommendPushButton_clicked();
    void on_appSelectionPushButton1_clicked();
    void on_appSelectionPushButton2_clicked();
    void on_appSelectionPushButton3_clicked();
    void on_appSelectionPushButton4_clicked();
    void on_appSelectionPushButton5_clicked();
    void on_appSelectionPushButton6_clicked();
    void on_appSelectionPushButton7_clicked();
    void on_appSelectionPushButton8_clicked();
    void on_appSelectionPushButton9_clicked();
    void on_leftPushButton_clicked();
    void on_rightPushButton_clicked();


private:
    QPixmap tickPixmap;
    QPixmap selectionButtonTickPixmap;
    QIcon upIcon;
    QIcon downIcon;
    QIcon leftIcon;
    QIcon rightIcon;
    QIcon upGrayIcon;
    QIcon downGraywnIcon;
    QIcon leftGrayIcon;
    QIcon rightGrayIcon;
    ChoosedOption *currentChoosedOption;
    QString chooseInstall;
    QString cancelChoose;
    AppList *appList;
    QHash<int, AppGrid *> appGridHash;
    QHash<int, QPixmap> starHash;
    int page;
    int size;
    int type;
    QSet<int> selectedAppIds;
    double totalAppSize;
    QHash<int, ChoosedAppItem *> choosedAppItemHash;
    QPixmap dotPixmap;
};

#endif // INSTALLATIONWIDGET_H
