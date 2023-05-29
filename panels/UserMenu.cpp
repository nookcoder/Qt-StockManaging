//
// Created by 김현욱 on 2023/05/30.
//

#include "UserMenu.h"
#include "user/SignUp.h"

UserMenu::UserMenu(QWidget *parent) : QWidget(parent){
    initUi();
}

void UserMenu::initUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    SignUp *signUp = new SignUp();
    tabWidget->addTab(signUp, "회원가입");
    backButton->setFixedSize(100,25);
    mainLayout->addWidget(backButton);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}