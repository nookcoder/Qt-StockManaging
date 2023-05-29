//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_STOCKMENU_H
#define STOCK_QT_PROJECT_STOCKMENU_H

#include <QApplication>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include "../components/SearchInput.h"

class StockMenu : public QWidget{
public:
    explicit StockMenu(QWidget* parent = nullptr);
    QPushButton *backButton = new QPushButton("뒤로가기");
    QHBoxLayout *topLayout = new QHBoxLayout();
    SearchInput *loginInput;
    QLineEdit *pEdit;
private:
    void initUi();

};


#endif //STOCK_QT_PROJECT_STOCKMENU_H
