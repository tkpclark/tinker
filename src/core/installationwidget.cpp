#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"

#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPalette>
#include <QBitmap>
#include <QHashIterator>


ChoosedOption::ChoosedOption(QPushButton *pushButton, QLabel *tickLabel)
{
    this->pushButton = pushButton;
    this->tickLabel = tickLabel;
}

AppGrid::AppGrid(QFrame *appFrame, QLabel *appPicLabel, QLabel *appNameLabel, QLabel *appSizeContentLabel, QLabel *appLevelLabel, bool selected)
{
    this->appFrame = appFrame;
    this->appPicLabel = appPicLabel;
    this->appNameLabel = appNameLabel;
    this->appSizeContentLabel = appSizeContentLabel;
    this->appLevelLabel = appLevelLabel;
    this->selected = selected;
}

InstallationWidget::InstallationWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);

    // init choice option tick
    QPixmap pixmap;
    if (!pixmap.load(":/images/tick.png")) {
        qWarning("Failed to load images/target.png");
    }
    this->tickPixmap = pixmap;

    // init app list tick
    QPixmap pm;
    if (!pm.load(":/images/choose.png")) {
        qWarning("Failed to load images/choose.png");
    }
    this->selectionButtonTickPixmap = pm;

    // init default option
    this->currentChoosedOption = new ChoosedOption(this->userChoicePushButton, this->userChoiceTickLabel);

    // init app selection button text
    this->chooseInstall = this->chooseInstall.fromLocal8Bit("选择安装");
    this->cancelChoose = this->cancelChoose.fromLocal8Bit("取消选择");

    // init time display
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(60000);    // update every 1 min

    // display user name
    TinkerMainWindow *tk = dynamic_cast<TinkerMainWindow*>(this->parent());
    if(tk->getUserName().isEmpty())
    {
        this->userNameWordLabel->setText("USER008");
    }
    else
    {
        this->userNameWordLabel->setText(tk->getUserName());
    }
    this->numLabel->setText("<font color='white'>1</font> 2 3 4 5 6 7 8 9");

    // init appList
    this->appList = new AppList;

    // init appGridHash
    this->appGridHash.insert(1, new AppGrid(this->appFrame1, this->appPicLabel1, this->appNameLabel1, this->appSizeContentLabel1, this->appLevelLabel1, false));
    this->appGridHash.insert(2, new AppGrid(this->appFrame2, this->appPicLabel2, this->appNameLabel2, this->appSizeContentLabel2, this->appLevelLabel2, false));
    this->appGridHash.insert(3, new AppGrid(this->appFrame3, this->appPicLabel3, this->appNameLabel3, this->appSizeContentLabel3, this->appLevelLabel3, false));
    this->appGridHash.insert(4, new AppGrid(this->appFrame4, this->appPicLabel4, this->appNameLabel4, this->appSizeContentLabel4, this->appLevelLabel4, false));
    this->appGridHash.insert(5, new AppGrid(this->appFrame5, this->appPicLabel5, this->appNameLabel5, this->appSizeContentLabel5, this->appLevelLabel5, false));
    this->appGridHash.insert(6, new AppGrid(this->appFrame6, this->appPicLabel6, this->appNameLabel6, this->appSizeContentLabel6, this->appLevelLabel6, false));
    this->appGridHash.insert(7, new AppGrid(this->appFrame7, this->appPicLabel7, this->appNameLabel7, this->appSizeContentLabel7, this->appLevelLabel7, false));
    this->appGridHash.insert(8, new AppGrid(this->appFrame8, this->appPicLabel8, this->appNameLabel8, this->appSizeContentLabel8, this->appLevelLabel8, false));
    this->appGridHash.insert(9, new AppGrid(this->appFrame9, this->appPicLabel9, this->appNameLabel9, this->appSizeContentLabel9, this->appLevelLabel9, false));

    // clear all the app
    this->hideAllAppGrid();

    // init star picture hash
    QPixmap starOnePm;
    if (!starOnePm.load(":/images/starOne.png")) {
        qWarning("Failed to load images/starOne.png");
    }
    this->starHash.insert(1, starOnePm);
    QPixmap starTwoPm;
    if (!starTwoPm.load(":/images/starTwo.png")) {
        qWarning("Failed to load images/starTwo.png");
    }
    this->starHash.insert(2, starTwoPm);
    QPixmap starThreePm;
    if (!starThreePm.load(":/images/starThree.png")) {
        qWarning("Failed to load images/starThree.png");
    }
    this->starHash.insert(3, starThreePm);
    QPixmap starFourPm;
    if (!starFourPm.load(":/images/starFour.png")) {
        qWarning("Failed to load images/starFour.png");
    }
    this->starHash.insert(4, starFourPm);
    QPixmap starFivePm;
    if (!starFivePm.load(":/images/starFive.png")) {
        qWarning("Failed to load images/starFive.png");
    }
    this->starHash.insert(5, starFivePm);

    // init default app grid
    this->displayAppList(TYPE_USER_CHOICE);
}

void InstallationWidget::hideAllAppGrid()
{
    QHashIterator<int, AppGrid *> iter(this->appGridHash);
    while(iter.hasNext()) {
        AppGrid *appGrid = iter.next().value();
        appGrid->appFrame->hide();
    }
}


void InstallationWidget::updateTime()
{
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
}

void InstallationWidget::on_exitPushButton_clicked()
{
    QCoreApplication::exit();
}

void InstallationWidget::changeOptionButtonAndAppList(int type, QPushButton *pushButton, QLabel *tickLabel)
{
    // update option size and display the tick
    if(this->currentChoosedOption->pushButton == pushButton)
    {
        return;
    }
    int pushButtonParentWidgetHeight = pushButton->parentWidget()->height();
    int pushButtonHeight = pushButton->height();
    int currentButtonParentWidgetHeight = this->currentChoosedOption->pushButton->parentWidget()->height();
    int currentButtonHeight = this->currentChoosedOption->pushButton->height();
    pushButton->parentWidget()->setFixedHeight(currentButtonParentWidgetHeight);
    pushButton->setFixedHeight(currentButtonHeight);
    tickLabel->setPixmap(this->tickPixmap);
    this->currentChoosedOption->pushButton->parentWidget()->setFixedHeight(pushButtonParentWidgetHeight);
    this->currentChoosedOption->pushButton->setFixedHeight(pushButtonHeight);
    this->currentChoosedOption->tickLabel->setPixmap(0);
    this->currentChoosedOption->pushButton = pushButton;
    this->currentChoosedOption->tickLabel = tickLabel;

    // display app list
    this->displayAppList(type);
}

void InstallationWidget::displayAppList(int type)
{
    this->hideAllAppGrid();
    QList<AppInfo *> appInfoList = this->appList->fetchApplist(type);
    int count = 1;
    QList<AppInfo *>::iterator it;
    for(it = appInfoList.begin(); it != appInfoList.end() && count<10; ++it)
    {
        AppInfo *app = *it;
        AppGrid * ag = this->appGridHash[count];
        ag->appNameLabel->setText(app->getName());
        ag->appPicLabel->setPixmap(app->getPic());
        ag->appSizeContentLabel->setText(QString::number(app->getSize()) + "M");
        ag->appLevelLabel->setPixmap(this->starHash[app->getLevel()]);
        ag->appFrame->show();
        count++;
    }
}

void InstallationWidget::on_userChoicePushButton_clicked()
{
    this->changeOptionButtonAndAppList(TYPE_USER_CHOICE, this->userChoicePushButton, this->userChoiceTickLabel);
}

void InstallationWidget::on_indispensablePushButton_clicked()
{
    this->changeOptionButtonAndAppList(TYPE_INDISPENSABLE, this->indispensablePushButton, this->indispensableTickLabel);
}

void InstallationWidget::on_fineGamePushButton_clicked()
{
    this->changeOptionButtonAndAppList(TYPE_FINE_GAME, this->fineGamePushButton, this->fineGameTickLabel);
}

void InstallationWidget::on_newAppPushButton_clicked()
{
    this->changeOptionButtonAndAppList(TYPE_NEW_APP, this->newAppPushButton, this->newAppTickLabel);
}

void InstallationWidget::on_recommendPushButton_clicked()
{
    this->changeOptionButtonAndAppList(TYPE_RECOMMEND, this->recommendPushButton, this->recommendTickLabel);
}

void InstallationWidget::changeSelectionState(QPushButton *pushButton, QLabel *tickLabel, int posion)
{
    const QPixmap *tickPixmap = tickLabel->pixmap();
    if(tickPixmap != 0 && !tickPixmap->isNull())
    {
        pushButton->setText(this->chooseInstall);
        tickLabel->setPixmap(0);
        QPalette pal = pushButton->palette();
        pal.setColor(QPalette::ButtonText, Qt::black);
        pushButton->setPalette(pal);
    }
    else
    {
        pushButton->setText(this->cancelChoose);
        tickLabel->setPixmap(this->selectionButtonTickPixmap);
        QPalette pal = pushButton->palette();
        pal.setColor(QPalette::ButtonText, QColor(178,178,178));
        pushButton->setPalette(pal);
    }
}

void InstallationWidget::on_appSelectionPushButton1_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton1, this->appTickPicLabel1, 1);
}

void InstallationWidget::on_appSelectionPushButton2_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton2, this->appTickPicLabel2, 2);
}

void InstallationWidget::on_appSelectionPushButton3_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton3, this->appTickPicLabel3, 3);
}

void InstallationWidget::on_appSelectionPushButton4_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton4, this->appTickPicLabel4, 4);
}

void InstallationWidget::on_appSelectionPushButton5_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton5, this->appTickPicLabel5, 5);
}

void InstallationWidget::on_appSelectionPushButton6_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton6, this->appTickPicLabel6, 6);
}

void InstallationWidget::on_appSelectionPushButton7_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton7, this->appTickPicLabel7, 7);
}

void InstallationWidget::on_appSelectionPushButton8_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton8, this->appTickPicLabel8, 8);
}

void InstallationWidget::on_appSelectionPushButton9_clicked()
{
    this->changeSelectionState(this->appSelectionPushButton9, this->appTickPicLabel9, 9);
}
