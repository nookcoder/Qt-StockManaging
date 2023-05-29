//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_ADDINGINTERESTINGCOMPANY_H
#define STOCK_QT_PROJECT_ADDINGINTERESTINGCOMPANY_H


#include <QWidget>
#include <QTableWidget>
#include "../StockMenu.h"
#include "string"
using namespace std;
class AddingInterestingCompany : public QWidget{
public:
    explicit AddingInterestingCompany(StockMenu* parent = nullptr);
    StockMenu* parent;
private:
    void initUi();
    void setTableWidgetByCompanyList(int type, string word);
    QTableWidget* table{};
};


#endif //STOCK_QT_PROJECT_ADDINGINTERESTINGCOMPANY_H
