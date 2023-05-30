//
// Created by 김현욱 on 2023/05/26.
//

#include "mainWindow.h"
#include "panels/MainMenu.h"
#include "panels/StockMenu.h"
#include "panels/UserMenu.h"
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

    MainMenu* mainMenu = new MainMenu(this, sqlController); // 메인 메뉴
    auto* stockMenu = new StockMenu(this, sqlController); // 주식 관련 메뉴
    auto* userMenu = new UserMenu(this, sqlController); // 유저 추가
    auto* checkingSchema = new CheckingSchema(this, sqlController);
    stack->addWidget(mainMenu);
    stack->addWidget(stockMenu);
    stack->addWidget(userMenu);
    stack->addWidget(checkingSchema);

    QPushButton::connect(mainMenu->signUpButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(userMenu);
    });
    QPushButton::connect(mainMenu->stockButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(stockMenu);
    });
    QPushButton::connect(mainMenu->schemasButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(checkingSchema);
    });
    QPushButton::connect(checkingSchema->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(mainMenu);
    });
    QPushButton::connect(stockMenu->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(mainMenu);
    });
    QPushButton::connect(userMenu->backButton, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(mainMenu);
    });


    stack->setCurrentWidget(mainMenu);
}