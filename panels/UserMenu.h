//
// Created by 김현욱 on 2023/05/30.
//

#ifndef STOCK_QT_PROJECT_USERMENU_H
#define STOCK_QT_PROJECT_USERMENU_H


#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QTabWidget>

class UserMenu : public QWidget{
public:
    explicit UserMenu(QWidget* parent = nullptr);
    QPushButton *backButton = new QPushButton("뒤로가기");
    QHBoxLayout *topLayout = new QHBoxLayout();
    QTabWidget *tabWidget = new QTabWidget();
private:
    void initUi();

};


#endif //STOCK_QT_PROJECT_USERMENU_H
