//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_USERMENU_H
#define STOCK_QT_PROJECT_USERMENU_H

#include "QWidget"
#include "QPushButton"
#include "../../components/MenuButton.h"
#include "../../mainWindow.h"

class UserMenu : public QWidget{
public:
    explicit UserMenu(QMainWindow *parent = nullptr); // constructor

    QPushButton* signUpButton = new MenuButton(this,"회원가입");
    QPushButton* stockButton = new MenuButton(this,"주식메뉴");
//    QPushButton* followingButton = new MenuButton(this,"팔로우");
private:
    void initUi();
    void turnPanel(QWidget* oldWidget, QWidget* newWidget);
};


#endif //STOCK_QT_PROJECT_USERMENU_H
