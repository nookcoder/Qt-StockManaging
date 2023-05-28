//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_DIVIDEND_H
#define STOCK_QT_PROJECT_DIVIDEND_H

#include "QWidget"
#include "QTabWidget"
#include "QBoxLayout"
#include "QLabel"
class Dividend : public QWidget{
public:
    explicit Dividend(QWidget* parent = nullptr);
private:
    void initUi();
};


#endif //STOCK_QT_PROJECT_DIVIDEND_H
