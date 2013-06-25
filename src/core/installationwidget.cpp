#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"
#include "src/include/detailwidget.h"

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
#include <QVariant>


ChoosedOption::ChoosedOption(QPushButton *pushButton, QLabel *tickLabel)
{
    this->pushButton = pushButton;
    this->tickLabel = tickLabel;
}

AppGrid::AppGrid(QFrame *appFrame, QPushButton *appPicPushButton, QLabel *appNameLabel, QLabel *appSizeContentLabel, QLabel *appLevelLabel, QWidget *appPicWordWidget, QFrame *appSelectionFrame, QPushButton *appSelectionPushButton, QLabel *appTickPicLabel)
{
    this->appFrame = appFrame;
    this->appPicPushButton = appPicPushButton;
    this->appNameLabel = appNameLabel;
    this->appSizeContentLabel = appSizeContentLabel;
    this->appLevelLabel = appLevelLabel;
    this->appPicWordWidget = appPicWordWidget;
    this->appSelectionFrame = appSelectionFrame;
    this->appSelectionPushButton = appSelectionPushButton;
    this->appTickPicLabel = appTickPicLabel;
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

    this->propertyName = "APP_DETAIL_PROPERTY_NAME";

    this->initPictures();

    // init default option
    this->currentChoosedOption = new ChoosedOption(this->userChoicePushButton, this->userChoiceTickLabel);

    // init app selection button text
    this->chooseInstall = this->chooseInstall.fromLocal8Bit("选择安装");
    this->cancelChoose = this->cancelChoose.fromLocal8Bit("取消选择");

    this->initTimer();

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

    this->initAppGridHash();

    this->initChoosedAppItemHash();

    this->page = PAGE_DEFAULT;
    this->size = SIZE_DEFAULT;
    this->type = TYPE_USER_CHOICE;

    // hide choosed app
    this->hideChoosedApp();

    this->installPushButton->setEnabled(false);

    // init default app grid
    this->displayAppList(type, page, size);
}

void InstallationWidget::initPictures()
{
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
}

void InstallationWidget::initTimer()
{
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(60000);    // update every 1 min
}

void InstallationWidget::initAppGridHash()
{
    this->appGridHash.insert(1, new AppGrid(this->appFrame1, this->appPicPushButton1, this->appNameLabel1, this->appSizeContentLabel1, this->appLevelLabel1, this->appPicWordWidget1, this->appSelectionFrame1, this->appSelectionPushButton1, this->appTickPicLabel1));
    this->appGridHash.insert(2, new AppGrid(this->appFrame2, this->appPicPushButton2, this->appNameLabel2, this->appSizeContentLabel2, this->appLevelLabel2, this->appPicWordWidget2, this->appSelectionFrame2, this->appSelectionPushButton2, this->appTickPicLabel2));
    this->appGridHash.insert(3, new AppGrid(this->appFrame3, this->appPicPushButton3, this->appNameLabel3, this->appSizeContentLabel3, this->appLevelLabel3, this->appPicWordWidget3, this->appSelectionFrame3, this->appSelectionPushButton3, this->appTickPicLabel3));
    this->appGridHash.insert(4, new AppGrid(this->appFrame4, this->appPicPushButton4, this->appNameLabel4, this->appSizeContentLabel4, this->appLevelLabel4, this->appPicWordWidget4, this->appSelectionFrame4, this->appSelectionPushButton4, this->appTickPicLabel4));
    this->appGridHash.insert(5, new AppGrid(this->appFrame5, this->appPicPushButton5, this->appNameLabel5, this->appSizeContentLabel5, this->appLevelLabel5, this->appPicWordWidget5, this->appSelectionFrame5, this->appSelectionPushButton5, this->appTickPicLabel5));
    this->appGridHash.insert(6, new AppGrid(this->appFrame6, this->appPicPushButton6, this->appNameLabel6, this->appSizeContentLabel6, this->appLevelLabel6, this->appPicWordWidget6, this->appSelectionFrame6, this->appSelectionPushButton6, this->appTickPicLabel6));
    this->appGridHash.insert(7, new AppGrid(this->appFrame7, this->appPicPushButton7, this->appNameLabel7, this->appSizeContentLabel7, this->appLevelLabel7, this->appPicWordWidget7, this->appSelectionFrame7, this->appSelectionPushButton7, this->appTickPicLabel7));
    this->appGridHash.insert(8, new AppGrid(this->appFrame8, this->appPicPushButton8, this->appNameLabel8, this->appSizeContentLabel8, this->appLevelLabel8, this->appPicWordWidget8, this->appSelectionFrame8, this->appSelectionPushButton8, this->appTickPicLabel8));
    this->appGridHash.insert(9, new AppGrid(this->appFrame9, this->appPicPushButton9, this->appNameLabel9, this->appSizeContentLabel9, this->appLevelLabel9, this->appPicWordWidget9, this->appSelectionFrame9, this->appSelectionPushButton9, this->appTickPicLabel9));
}

void InstallationWidget::initChoosedAppItemHash()
{
    this->choosedAppItemHash.insert(1, new ChoosedAppItem(this->choosedAppDotLabel1, this->choosedAppNameLabel1));
    this->choosedAppItemHash.insert(2, new ChoosedAppItem(this->choosedAppDotLabel2, this->choosedAppNameLabel2));
    this->choosedAppItemHash.insert(3, new ChoosedAppItem(this->choosedAppDotLabel3, this->choosedAppNameLabel3));
    this->choosedAppItemHash.insert(4, new ChoosedAppItem(this->choosedAppDotLabel4, this->choosedAppNameLabel4));
    this->choosedAppItemHash.insert(5, new ChoosedAppItem(this->choosedAppDotLabel5, this->choosedAppNameLabel5));
    this->choosedAppItemHash.insert(6, new ChoosedAppItem(this->choosedAppDotLabel6, this->choosedAppNameLabel6));
}

void InstallationWidget::hideAllAppGrid()
{
    QHashIterator<int, AppGrid *> iter(this->appGridHash);
    while(iter.hasNext()) {
        AppGrid *appGrid = iter.next().value();
        appGrid->appPicWordWidget->hide();
        appGrid->appSelectionFrame->hide();
        this->disconnect(appGrid->appPicPushButton, SIGNAL(clicked()), this, SLOT(enterDetailPage()));
    }
}

void InstallationWidget::hideChoosedApp()
{
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

    this->selectedAppHash.clear();

    this->hideChoosedApp();

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
        ag->appInfo = app;
        ag->appNameLabel->setText(app->getName());
        ag->appPicPushButton->setIcon(QPixmap(app->getPic()));
        QVariant var;
        var.setValue(app);
        ag->appPicPushButton->setProperty(this->propertyName, var);
        ag->appSizeContentLabel->setText(QString::number(app->getSize()) + "M");
        ag->appLevelLabel->setPixmap(this->starHash[app->getLevel()]);
//        ag->appFrame->setStyleSheet("background-color: rgb(223,223,223);");
        ag->appSelectionPushButton->setText(this->chooseInstall);
        ag->appTickPicLabel->setPixmap(0);
        QPalette pal = ag->appSelectionPushButton->palette();
        pal.setColor(QPalette::ButtonText, Qt::black);
        ag->appSelectionPushButton->setPalette(pal);
        if(this->selectedAppHash.contains(app->getId()))
        {
            this->toSelectedState(ag->appSelectionPushButton, ag->appTickPicLabel);
        }
        else
        {
            this->toCancelledState(ag->appSelectionPushButton, ag->appTickPicLabel);
        }
        ag->appPicWordWidget->show();
        ag->appSelectionFrame->show();
        this->connect(ag->appPicPushButton, SIGNAL(clicked()), this, SLOT(enterDetailPage()));
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
    AppInfo *app = this->appGridHash[position]->appInfo;
    if(tickPixmap != 0 && !tickPixmap->isNull())
    {
        this->toCancelledState(pushButton, tickLabel);
        this->selectedAppHash.remove(app->getId());
        QHashIterator<int, ChoosedAppItem *> iter(this->choosedAppItemHash);
        while(iter.hasNext())
        {
            ChoosedAppItem * appItem = iter.next().value();
            if(appItem->appId == app->getId()) {
                this->hideChoosedApp();
                QHashIterator<int, AppInfo *> it(this->selectedAppHash);
                for(int i = 1; it.hasNext() && i <= this->choosedAppItemHash.size(); ++i)
                {
                    AppInfo *appInfo = it.next().value();
                    ChoosedAppItem * item = this->choosedAppItemHash[i];
                    item->appId = appInfo->getId();
                    item->choosedAppNameLabel->setText(appInfo->getName());
                    item->choosedAppDotLabel->show();
                    item->choosedAppNameLabel->show();
                }
                break;
            }
        }
        if(this->selectedAppHash.isEmpty()) {
            this->choosedSumLabel->setText("");
            this->installPushButton->setEnabled(false);
        }
        else
        {
            this->totalAppSize -= app->getSize();
            QString text;
            text.append(text.fromLocal8Bit("共")).append(QString::number(this->selectedAppHash.size())).append(text.fromLocal8Bit("款应用\n")).append(text.fromLocal8Bit("共")).append(QString::number(this->totalAppSize)).append("M");
            this->choosedSumLabel->setText(text);
        }
    }
    else
    {
        this->installPushButton->setEnabled(true);
        this->toSelectedState(pushButton, tickLabel);
        this->selectedAppHash.insert(app->getId(), app);
        if(this->selectedAppHash.size() <= this->choosedAppItemHash.size()) {
            ChoosedAppItem * appItem = this->choosedAppItemHash[this->selectedAppHash.size()];
            appItem->choosedAppDotLabel->setPixmap(this->dotPixmap);
            appItem->choosedAppNameLabel->setText(app->getName());
            appItem->appId = app->getId();
            appItem->choosedAppDotLabel->show();
            appItem->choosedAppNameLabel->show();
        }
        this->totalAppSize += app->getSize();
        QString text;
        text.append(text.fromLocal8Bit("共")).append(QString::number(this->selectedAppHash.size())).append(text.fromLocal8Bit("款应用\n")).append(text.fromLocal8Bit("共")).append(QString::number(this->totalAppSize)).append("M");
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

void InstallationWidget::on_installPushButton_clicked()
{
    this->appList->installApplist(this->selectedAppHash.values());
    this->selectedAppHash.clear();
    this->hideChoosedApp();
    QHashIterator<int, AppGrid *> iter(this->appGridHash);
    while(iter.hasNext()) {
        AppGrid *appGrid = iter.next().value();
        this->toCancelledState(appGrid->appSelectionPushButton, appGrid->appTickPicLabel);
    }
    this->installPushButton->setEnabled(false);
}

void InstallationWidget::enterDetailPage()
{
    this->appListWidget->hide();
    this->pageWidget->hide();
    DetailWidget *detailWidget = new DetailWidget(this);
    this->verticalLayout->addWidget(detailWidget);
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    detailWidget->displayAppDetail(btn->property(this->propertyName).value<AppInfo *>());
    detailWidget->show();
}
