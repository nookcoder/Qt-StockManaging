//
// Created by 김현욱 on 2023/05/27.
//

#include "StockMenu.h"
#include "MyStock.h"
#include "Dividend.h"
#include "Following.h"
#include "interestingCompany.h"

StockMenu::StockMenu(QWidget *parent) : QWidget(parent) {
    initUi();
}

void StockMenu::initUi() {
    // 상단 메뉴
    QLineEdit *pEdit = new QLineEdit();
    pEdit->setPlaceholderText("이메일을 입력해주세요");
    loginInput = new SearchInput(this, new QLabel("로그인"), pEdit, "로그인");
    topLayout->addWidget(backButton);
    topLayout->addStretch(1);
    topLayout->addWidget(loginInput);

    // 메인 컴포넌트
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QTabWidget *tabWidget = new QTabWidget();
    MyStock *myStock = new MyStock(tabWidget); // 나의 주식
    Dividend *dividend = new Dividend(tabWidget); // 나의 배당
    Following *following = new Following(tabWidget); //
    interestingCompany *interesting = new interestingCompany(tabWidget); // 나의 관심종목
    tabWidget->addTab(myStock, "나의 주식");
    tabWidget->addTab(dividend, "나의 배당");
    tabWidget->addTab(interesting, "관심 종목");
    tabWidget->addTab(following, "다른 사람 주식");
    // 레이아웃 추가
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
