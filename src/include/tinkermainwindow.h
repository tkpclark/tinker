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
    void initEnv();
    void initMainWindow();
    void initOtherWidgets();

signals:

public slots:
    void on_loginPushButton_clicked();

private:

};

#endif // TINKERMAINWINDOW_H
