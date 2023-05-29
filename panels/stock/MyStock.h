//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_MYSTOCK_H
#define STOCK_QT_PROJECT_MYSTOCK_H

#include "QWidget"
#include "QTabWidget"
#include "QBoxLayout"
#include "QLabel"
class MyStock : public QWidget{
public:
    explicit MyStock(QWidget* parent = nullptr);
    void initUi();
};


#endif //STOCK_QT_PROJECT_MYSTOCK_H
