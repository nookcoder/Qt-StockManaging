//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_MYSTOCK_H
#define STOCK_QT_PROJECT_MYSTOCK_H

#include "QWidget"
#include "QTabWidget"
#include "QBoxLayout"
#include "QLabel"
#include "../StockMenu.h"
#include <QTableWidget>

class MyStock : public QWidget{
public:
    explicit MyStock(StockMenu* parent = nullptr);
    StockMenu* parent;
    void initUi();
private:
    MyStockDto* getMyStock();
    QTableWidget* table;\
    void setTableWidget(MyStockDto* myStock);
};


#endif //STOCK_QT_PROJECT_MYSTOCK_H
