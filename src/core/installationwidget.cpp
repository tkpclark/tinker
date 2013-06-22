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
#include <qmath.h>


ChoosedOption::ChoosedOption(QPushButton *pushButton, QLabel *tickLabel)
{
    this->pushButton = pushButton;
    this->tickLabel = tickLabel;
}

AppGrid::AppGrid(QFrame *appFrame, QLabel *appPicLabel, QLabel *appNameLabel, QLabel *appSizeContentLabel, QLabel *appLevelLabel, QWidget *appPicWordWidget, QFrame *appSelectionFrame, QPushButton *appSelectionPushButton, QLabel *appTickPicLabel, bool selected)
{
    this->appFrame = appFrame;
    this->appPicLabel = appPicLabel;
    this->appNameLabel = appNameLabel;
    this->appSizeContentLabel = appSizeContentLabel;
    this->appLevelLabel = appLevelLabel;
    this->appPicWordWidget = appPicWordWidget;
    this->appSelectionFrame = appSelectionFrame;
    this->appSelectionPushButton = appSelectionPushButton;
    this->appTickPicLabel = appTickPicLabel;
    this->selected = selected;
}

ChoosedAppItem::ChoosedAppItem(QLabel *choosedAppDotLabel, QLabel *choosedAppNameLabel)
{
    this->choosedAppDotLabel = choosedAppDotLabel;
    this->choosedAppNameLabel = choosedAppNameLabel;
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

    // init page turning icon
    QPixmap upPixmap;
    if (!upPixmap.load(":/images/up.png")) {
        qWarning("Failed to load images/up.png");
    }
    this->upIcon = QIcon(upPixmap);
    QPixmap downPixmap;
    if (!downPixmap.load(":/images/down.png")) {
        qWarning("Failed to load images/down.png");
    }
    this->downIcon = QIcon(downPixmap);
    QPixmap leftPixmap;
    if (!leftPixmap.load(":/images/left.png")) {
        qWarning("Failed to load images/left.png");
    }
    this->leftIcon = QIcon(leftPixmap);
    QPixmap rightPixmap;
    if (!rightPixmap.load(":/images/right.png")) {
        qWarning("Failed to load images/right.png");
    }
    this->rightIcon = QIcon(rightPixmap);
    QPixmap upGrayPixmap;
    if (!upGrayPixmap.load(":/images/up_gray.png")) {
        qWarning("Failed to load images/up_gray.png");
    }
    this->upGrayIcon = QIcon(upGrayPixmap);
    QPixmap downGrayPixmap;
    if (!downGrayPixmap.load(":/images/down_gray.png")) {
        qWarning("Failed to load images/down_gray.png");
    }
    this->downIcon = QIcon(downGrayPixmap);
    QPixmap leftGrayPixmap;
    if (!leftGrayPixmap.load(":/images/left_gray.png")) {
        qWarning("Failed to load images/left_gray.png");
    }
    this->leftGrayIcon = QIcon(leftGrayPixmap);
    QPixmap rightGrayPixmap;
    if (!rightGrayPixmap.load(":/images/right_gray.png")) {
        qWarning("Failed to load images/right_gray.png");
    }
    this->rightGrayIcon = QIcon(rightGrayPixmap);

    // init dot pixmap
    QPixmap dotPixmap;
    if (!dotPixmap.load(":/images/dot.png")) {
        qWarning("Failed to load images/dot.png");
    }
    this->dotPixmap = dotPixmap;

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

    // init appList
    this->appList = new AppList;

    // init appGridHash
    this->appGridHash.insert(1, new AppGrid(this->appFrame1, this->appPicLabel1, this->appNameLabel1, this->appSizeContentLabel1, this->appLevelLabel1, this->appPicWordWidget1, this->appSelectionFrame1, this->appSelectionPushButton1, this->appTickPicLabel1, false));
    this->appGridHash.insert(2, new AppGrid(this->appFrame2, this->appPicLabel2, this->appNameLabel2, this->appSizeContentLabel2, this->appLevelLabel2, this->appPicWordWidget2, this->appSelectionFrame2, this->appSelectionPushButton2, this->appTickPicLabel2, false));
    this->appGridHash.insert(3, new AppGrid(this->appFrame3, this->appPicLabel3, this->appNameLabel3, this->appSizeContentLabel3, this->appLevelLabel3, this->appPicWordWidget3, this->appSelectionFrame3, this->appSelectionPushButton3, this->appTickPicLabel3, false));
    this->appGridHash.insert(4, new AppGrid(this->appFrame4, this->appPicLabel4, this->appNameLabel4, this->appSizeContentLabel4, this->appLevelLabel4, this->appPicWordWidget4, this->appSelectionFrame4, this->appSelectionPushButton4, this->appTickPicLabel4, false));
    this->appGridHash.insert(5, new AppGrid(this->appFrame5, this->appPicLabel5, this->appNameLabel5, this->appSizeContentLabel5, this->appLevelLabel5, this->appPicWordWidget5, this->appSelectionFrame5, this->appSelectionPushButton5, this->appTickPicLabel5, false));
    this->appGridHash.insert(6, new AppGrid(this->appFrame6, this->appPicLabel6, this->appNameLabel6, this->appSizeContentLabel6, this->appLevelLabel6, this->appPicWordWidget6, this->appSelectionFrame6, this->appSelectionPushButton6, this->appTickPicLabel6, false));
    this->appGridHash.insert(7, new AppGrid(this->appFrame7, this->appPicLabel7, this->appNameLabel7, this->appSizeContentLabel7, this->appLevelLabel7, this->appPicWordWidget7, this->appSelectionFrame7, this->appSelectionPushButton7, this->appTickPicLabel7, false));
    this->appGridHash.insert(8, new AppGrid(this->appFrame8, this->appPicLabel8, this->appNameLabel8, this->appSizeContentLabel8, this->appLevelLabel8, this->appPicWordWidget8, this->appSelectionFrame8, this->appSelectionPushButton8, this->appTickPicLabel8, false));
    this->appGridHash.insert(9, new AppGrid(this->appFrame9, this->appPicLabel9, this->appNameLabel9, this->appSizeContentLabel9, this->appLevelLabel9, this->appPicWordWidget9, this->appSelectionFrame9, this->appSelectionPushButton9, this->appTickPicLabel9, false));

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

    // init choosed app item
    this->choosedAppItemHash.insert(1, new ChoosedAppItem(this->choosedAppDotLabel1, this->choosedAppNameLabel1));
    this->choosedAppItemHash.insert(2, new ChoosedAppItem(this->choosedAppDotLabel2, this->choosedAppNameLabel2));
    this->choosedAppItemHash.insert(3, new ChoosedAppItem(this->choosedAppDotLabel3, this->choosedAppNameLabel3));
    this->choosedAppItemHash.insert(4, new ChoosedAppItem(this->choosedAppDotLabel4, this->choosedAppNameLabel4));
    this->choosedAppItemHash.insert(5, new ChoosedAppItem(this->choosedAppDotLabel5, this->choosedAppNameLabel5));
    this->choosedAppItemHash.insert(6, new ChoosedAppItem(this->choosedAppDotLabel6, this->choosedAppNameLabel6));

    this->page = PAGE_DEFAULT;
    this->size = SIZE_DEFAULT;
    this->type = TYPE_USER_CHOICE;

    // init default app grid
    this->displayAppList(type, page, size);
}

void InstallationWidget::hideAllAppGrid()
{
    QHashIterator<int, AppGrid *> iter(this->appGridHash);
    while(iter.hasNext()) {
        AppGrid *appGrid = iter.next().value();
        appGrid->appPicWordWidget->hide();
        appGrid->appSelectionFrame->hide();
    }

    // hide choosed wiget
    QHashIterator<int, ChoosedAppItem *> it(this->choosedAppItemHash);
    while(it.hasNext()) {
        ChoosedAppItem *choosedAppItem = it.next().value();
        choosedAppItem->choosedAppDotLabel->hide();
        choosedAppItem->choosedAppNameLabel->hide();
    }
    this->choosedSumLabel->setText("");
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
    this->type = type;
    this->page = PAGE_DEFAULT;
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

    this->selectedAppIds.clear();

    // display app list
    this->displayAppList(type, PAGE_DEFAULT, SIZE_DEFAULT);
}

void InstallationWidget::displayAppList(int type, int page, int size)
{
    this->hideAllAppGrid();
    QList<AppInfo *> appInfoList = this->appList->fetchApplist(type);
    int count = 0;
    for(int i = (page-1)*size; i < appInfoList.size() && i <page*size; ++i)
    {
        AppInfo *app = appInfoList.at(i);
        AppGrid * ag = this->appGridHash[++count];
        ag->appId = app->getId();
        ag->appSize = app->getSize();
        ag->appNameLabel->setText(app->getName());
        ag->appPicLabel->setPixmap(app->getPic());
        ag->appSizeContentLabel->setText(QString::number(app->getSize()) + "M");
        ag->appLevelLabel->setPixmap(this->starHash[app->getLevel()]);
//        ag->appFrame->setStyleSheet("background-color: rgb(223,223,223);");
        ag->appSelectionPushButton->setText(this->chooseInstall);
        ag->appTickPicLabel->setPixmap(0);
        QPalette pal = ag->appSelectionPushButton->palette();
        pal.setColor(QPalette::ButtonText, Qt::black);
        ag->appSelectionPushButton->setPalette(pal);
        if(this->selectedAppIds.contains(ag->appId))
        {
            this->toSelectedState(ag->appSelectionPushButton, ag->appTickPicLabel);
        }
        else
        {
            this->toCancelledState(ag->appSelectionPushButton, ag->appTickPicLabel);
        }
        ag->appPicWordWidget->show();
        ag->appSelectionFrame->show();
    }
    if(page == 1)
    {
        this->leftPushButton->setEnabled(false);
        this->leftPushButton->setIcon(this->leftGrayIcon);
    }
    else
    {
        this->leftPushButton->setEnabled(true);
        this->leftPushButton->setIcon(this->leftIcon);
    }
    if(page*size < appInfoList.size())
    {
        this->rightPushButton->setEnabled(true);
        this->rightPushButton->setIcon(this->rightIcon);
    }
    else
    {
        this->rightPushButton->setEnabled(false);
        this->rightPushButton->setIcon(this->rightGrayIcon);
    }
    int totalPage = ceil(appInfoList.size()/(double)size);
    QString numText;
    for(int i = 1; i <= totalPage; ++i)
    {
        if(i == page)
        {
            numText.append("<font color='white'>").append(QString::number(i)).append("</font> ");
        }
        else
        {
            numText.append(QString::number(i)).append(" ");
        }
    }
    numText.resize(numText.size() - 1);
    this->numLabel->setText(numText);

//    for(int i = count; i < 9;) {
//        this->appGridHash[++i]->appFrame->setStyleSheet("background-color: rgb(47,47,47);");
//    }
}

void InstallationWidget::addSelectedApp(int appId)
{
    this->selectedAppIds.insert(appId);
}

void InstallationWidget::removeSelectedApp(int appId)
{
    this->selectedAppIds.remove(appId);
}

void InstallationWidget::toCancelledState(QPushButton *appSelectionPushButton, QLabel *appTickPicLabel)
{
    appSelectionPushButton->setText(this->chooseInstall);
    appTickPicLabel->setPixmap(0);
    QPalette pal = appSelectionPushButton->palette();
    pal.setColor(QPalette::ButtonText, Qt::black);
    appSelectionPushButton->setPalette(pal);
}

void InstallationWidget::toSelectedState(QPushButton *appSelectionPushButton, QLabel *appTickPicLabel)
{
    appSelectionPushButton->setText(this->cancelChoose);
    appTickPicLabel->setPixmap(this->selectionButtonTickPixmap);
    QPalette pal = appSelectionPushButton->palette();
    pal.setColor(QPalette::ButtonText, QColor(178,178,178));
    appSelectionPushButton->setPalette(pal);
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

void InstallationWidget::changeSelectionState(QPushButton *pushButton, QLabel *tickLabel, int position)
{
    const QPixmap *tickPixmap = tickLabel->pixmap();
    if(tickPixmap != 0 && !tickPixmap->isNull())
    {
        this->toCancelledState(pushButton, tickLabel);
        this->removeSelectedApp(this->appGridHash[position]->appId);
        if(this->selectedAppIds.size() < this->choosedAppItemHash.size()) {
            ChoosedAppItem * appItem = this->choosedAppItemHash[this->selectedAppIds.size()+1];
            appItem->choosedAppDotLabel->hide();
            appItem->choosedAppNameLabel->hide();
        }
        this->totalAppSize -= this->appGridHash[position]->appSize;
        QString text;
        text.append(text.fromLocal8Bit("共")).append(QString::number(this->selectedAppIds.size())).append(text.fromLocal8Bit("款应用")).append(text.fromLocal8Bit("共")).append(QString::number(this->totalAppSize)).append("M");
        this->choosedSumLabel->setText(text);
        if(this->selectedAppIds.isEmpty()) {
            this->choosedSumLabel->setText("");
        }
    }
    else
    {
        this->toSelectedState(pushButton, tickLabel);
        this->addSelectedApp(this->appGridHash[position]->appId);
        if(this->selectedAppIds.size() <= this->choosedAppItemHash.size()) {
            ChoosedAppItem * appItem = this->choosedAppItemHash[this->selectedAppIds.size()];
            appItem->choosedAppDotLabel->setPixmap(this->dotPixmap);
            appItem->choosedAppNameLabel->setText(this->appGridHash[position]->appNameLabel->text());
            appItem->choosedAppDotLabel->show();
            appItem->choosedAppNameLabel->show();
        }
        this->totalAppSize += this->appGridHash[position]->appSize;
        QString text;
        text.append(text.fromLocal8Bit("共")).append(QString::number(this->selectedAppIds.size())).append(text.fromLocal8Bit("款应用")).append(text.fromLocal8Bit("共")).append(QString::number(this->totalAppSize)).append("M");
        this->choosedSumLabel->setText(text);
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

void InstallationWidget::on_leftPushButton_clicked()
{
    this->displayAppList(this->type, --this->page, this->size);
}

void InstallationWidget::on_rightPushButton_clicked()
{
    this->displayAppList(this->type, ++this->page, this->size);
}
