//
// Created by 김현욱 on 2023/05/27.
//

#include "StockMenu.h"
#include "stock/MyStock.h"
#include "stock/Dividend.h"
#include "user/Following.h"
#include "interesting/interestingCompany.h"
#include "interesting/AddingInterestingCompany.h"
#include "../database/SQLController.h"
#include "../constants/type/UserSearchType.cpp"
StockMenu::StockMenu(QWidget *parent) : QWidget(parent) {
    initUi();
}

void StockMenu::initUi() {
    // 상단 메뉴
    pEdit = new QLineEdit();
    pEdit->setPlaceholderText("이메일을 입력해주세요");
    loginInput = new SearchInput(this, new QLabel("로그인"), pEdit, "로그인");
    topLayout->addWidget(backButton);
    topLayout->addStretch(1);
    topLayout->addWidget(loginInput);
    QPushButton::connect(loginInput->searchButton, &QPushButton::clicked, [=](){
        if(pEdit->isEnabled()) {
            Member* member = SQLController::getMember(UserSearchType::EMAIL,pEdit->text().toStdString().c_str());
            if(member[0].email != "-1") {
                pEdit->setEnabled(false);
                loginInput->searchButton->setText("로그아웃");
            } else {
                pEdit->setText("");
                pEdit->setPlaceholderText("존재하지 않는 이메일입니다");
            }
        } else {
            pEdit->setEnabled(true);
            loginInput->searchButton->setText("로그인");
        }
    });
    // 메인 컴포넌트
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QTabWidget *tabWidget = new QTabWidget();
    MyStock *myStock = new MyStock(tabWidget); // 나의 주식
    Dividend *dividend = new Dividend(tabWidget); // 나의 배당
    Following *following = new Following(tabWidget); //
    interestingCompany *interesting = new interestingCompany(this); // 나의 관심종목
    AddingInterestingCompany *addingInterestingCompany = new AddingInterestingCompany(this); // 관심종목 추가
    tabWidget->addTab(myStock, "나의 주식");
    tabWidget->addTab(dividend, "나의 배당");
    tabWidget->addTab(interesting, "나의 관심 종목");
    tabWidget->addTab(addingInterestingCompany, "종목 검색");
    tabWidget->addTab(following, "다른 사람 주식");
    // 레이아웃 추가
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
