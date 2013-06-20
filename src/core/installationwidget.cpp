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


ChoosedOption::ChoosedOption(QPushButton *pushButton, QLabel *tickLabel)
{
    this->pushButton = pushButton;
    this->tickLabel = tickLabel;
}

AppGrid::AppGrid(QLabel *appPicLabel, QLabel *appNameLabel, QLabel *appSizeContentLabel, QLabel *appLevelLabel, bool selected)
{
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
    this->appGridHash.insert(1, new AppGrid(this->appPicLabel1, this->appNameLabel1, this->appSizeContentLabel1, this->appLevelLabel1, false));
    this->appGridHash.insert(2, new AppGrid(this->appPicLabel2, this->appNameLabel2, this->appSizeContentLabel2, this->appLevelLabel2, false));
    this->appGridHash.insert(3, new AppGrid(this->appPicLabel3, this->appNameLabel3, this->appSizeContentLabel3, this->appLevelLabel3, false));
    this->appGridHash.insert(4, new AppGrid(this->appPicLabel4, this->appNameLabel4, this->appSizeContentLabel4, this->appLevelLabel4, false));
    this->appGridHash.insert(5, new AppGrid(this->appPicLabel5, this->appNameLabel5, this->appSizeContentLabel5, this->appLevelLabel5, false));
    this->appGridHash.insert(6, new AppGrid(this->appPicLabel6, this->appNameLabel6, this->appSizeContentLabel6, this->appLevelLabel6, false));
    this->appGridHash.insert(7, new AppGrid(this->appPicLabel7, this->appNameLabel7, this->appSizeContentLabel7, this->appLevelLabel7, false));
    this->appGridHash.insert(8, new AppGrid(this->appPicLabel8, this->appNameLabel8, this->appSizeContentLabel8, this->appLevelLabel8, false));
    this->appGridHash.insert(9, new AppGrid(this->appPicLabel9, this->appNameLabel9, this->appSizeContentLabel9, this->appLevelLabel9, false));
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
    QList<AppInfo *> appInfoList = this->appList->fetchApplist(type);
    int count = 0;
    QList<AppInfo *>::iterator it;
    for(it = appInfoList.begin(); it != appInfoList.end(); ++it)
    {
        AppInfo *app = *it;
        qDebug() << app->getId()          \
                 << app->getName()        \
                 << app->getSize()        \
                 << app->getSummary()     \
                 << app->getDetail()      \
                 << app->getLevel()       \
                 << app->getPic().size();

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
