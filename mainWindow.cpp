//
// Created by 김현욱 on 2023/05/26.
//

#include "mainWindow.h"
#include "panels/user/SignUp.h"
#include "panels/UserMenu.h"
#include "panels/StockMenu.h"
#include "iostream"
#include "database/SQLController.h"
#include "panels/schmas/CheckingSchema.h"

mainWindow::mainWindow() {
}

void mainWindow::run() {
    init();
    mainLayout->addWidget(stack);
//    mainLayout->setAlignment(Qt::AlignCenter);
    main->setLayout(mainLayout);
    setCentralWidget(main);
    this->setLayout(mainLayout);
    this->setWindowTitle("StockProject");
    this->setFixedSize(800, 600);
    this->show();
}

void mainWindow::init() {
    stack = new QStackedWidget(this);

    auto* userMenu = new UserMenu(this); // 사용자 메뉴
    auto* stockMenu = new StockMenu(this); // 주식 관련 메뉴
    auto* signUp = new SignUp(this); // 유저 추가
    auto* checkingSchema = new CheckingSchema(this);
    stack->addWidget(userMenu);
    stack->addWidget(stockMenu);
    stack->addWidget(signUp);
    stack->addWidget(checkingSchema);

    QPushButton::connect(userMenu->signUpButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(signUp);
    });
    QPushButton::connect(userMenu->stockButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(stockMenu);
    });
    QPushButton::connect(userMenu->schemasButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(checkingSchema);
    });
    QPushButton::connect(checkingSchema->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(userMenu);
    });
    QPushButton::connect(stockMenu->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(userMenu);
    });
    QPushButton::connect(signUp->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(userMenu);
    });


    stack->setCurrentWidget(userMenu);
}