#include "src/include/installationwidget.h"
#include "src/include/tinkermainwindow.h"
#include "src/include/applist.h"

#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPalette>


ChoosedOption::ChoosedOption(QPushButton *pushButton, QLabel *tickLabel)
{
    this->pushButton = pushButton;
    this->tickLabel = tickLabel;
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
    this->initOtherWidgets();

}

void InstallationWidget::initOtherWidgets()
{
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

}


void InstallationWidget::updateTime()
{
    this->timeLabel->setText(QDateTime::currentDateTime().toString("hh:mm AP"));
}

void InstallationWidget::on_exitPushButton_clicked()
{
    QCoreApplication::exit();
}

void InstallationWidget::displayAppList(int type, QPushButton *pushButton, QLabel *tickLabel)
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
    AppList appList;
    QList<AppInfo *> appInfoList = appList.fetchApplist(type);
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
    this->displayAppList(TYPE_USER_CHOICE, this->userChoicePushButton, this->userChoiceTickLabel);
}

void InstallationWidget::on_indispensablePushButton_clicked()
{
    this->displayAppList(TYPE_INDISPENSABLE, this->indispensablePushButton, this->indispensableTickLabel);
}

void InstallationWidget::on_fineGamePushButton_clicked()
{
    this->displayAppList(TYPE_FINE_GAME, this->fineGamePushButton, this->fineGameTickLabel);
}

void InstallationWidget::on_newAppPushButton_clicked()
{
    this->displayAppList(TYPE_NEW_APP, this->newAppPushButton, this->newAppTickLabel);
}

void InstallationWidget::on_recommendPushButton_clicked()
{
    this->displayAppList(TYPE_RECOMMEND, this->recommendPushButton, this->recommendTickLabel);
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
