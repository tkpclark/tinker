#ifndef TINKERMAINWINDOW_H
#define TINKERMAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include "ui_mainwindow.h"

class TinkerMainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    explicit TinkerMainWindow(QWidget *parent = 0);
    void initMainWindow();
    void initOtherWidgets();
    QString getUserName();
    void initEnv();

signals:

public slots:
    void on_loginPushButton_clicked();

private:
    QString userName;

};

#endif // TINKERMAINWINDOW_H
