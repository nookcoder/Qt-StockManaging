//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_MAINMENU_H
#define STOCK_QT_PROJECT_MAINMENU_H

#include "QWidget"
#include "QPushButton"
#include "../components/MenuButton.h"
#include "../mainWindow.h"
#include "../database/SQLController.h"

class MainMenu : public QWidget{
public:
    explicit MainMenu(QMainWindow *parent = nullptr, SQLController* sqlController= nullptr);
    // constructor

    QPushButton* schemasButton = new MenuButton(this, "Check Schema");
    QPushButton* signUpButton = new MenuButton(this,"회원메뉴");
    QPushButton* stockButton = new MenuButton(this,"주식메뉴");
//    QPushButton* followingButton = new MenuButton(this,"팔로우");
private:
    void initUi();
    void turnPanel(QWidget* oldWidget, QWidget* newWidget);
};


#endif //STOCK_QT_PROJECT_MAINMENU_H
