//
// Created by 김현욱 on 2023/05/28.
//

#ifndef STOCK_QT_PROJECT_INTERESTINGCOMPANY_H
#define STOCK_QT_PROJECT_INTERESTINGCOMPANY_H


#include <QWidget>
#include "string"
#include <QTableWidget>
#include "../StockMenu.h"

using namespace std;
class interestingCompany: public QWidget{
public:
    explicit interestingCompany(StockMenu* parent = nullptr);
    StockMenu* parent;

private:
    void initUi();
    void setTableWidgetByCompanyList(int type, string word);
    QTableWidget* table;
};


#endif //STOCK_QT_PROJECT_INTERESTINGCOMPANY_H
