
//
// Created by 김현욱 on 2023/05/26.
//

#ifndef STOCK_QT_PROJECT_MAINWINDOW_H
#define STOCK_QT_PROJECT_MAINWINDOW_H

#include "QMainWindow"
#include "QStackedWidget"
#include <QVBoxLayout>
#include "QWidget"
#include "panels/UserMenu.h"

class mainWindow: public QMainWindow{
public:
    explicit mainWindow();
    void run();

    QStackedWidget *stack; // stack of panels

    QWidget *main = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
private:
    void init();

};


#endif //STOCK_QT_PROJECT_MAINWINDOW_H
