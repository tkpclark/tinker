#include "src/include/detailwidget.h"

DetailWidget::DetailWidget(QWidget *parent) :
        QWidget(parent)
{
    this->setupUi(this);
    InstallationWidget *iw = dynamic_cast<InstallationWidget*>(parent);
    this->parent = iw;
}

void DetailWidget::displayAppDetail(AppInfo *appInfo)
{
    this->appPicLabel->setPixmap(appInfo->getPic());
    this->appNameLabel->setText(appInfo->getName());
    this->appSizeContentLabel->setText(QString::number(appInfo->getSize()) + "M");
    this->appLevelLabel->setPixmap(this->parent->starHash[appInfo->getLevel()]);
    this->appIntroLabel->setText(appInfo->getSummary());
    this->appDetailTextEdit->setText(appInfo->getDetail().replace(QString("\\n"), "<br/>"));
    this->appPosterPicLabel->setPixmap(appInfo->getPosterPic());
}

void DetailWidget::on_backPushButton_clicked()
{
    this->hide();
    this->parent->appListWidget->show();
    this->parent->pageWidget->show();
    delete this;
}
