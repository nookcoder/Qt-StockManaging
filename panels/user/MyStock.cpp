//
// Created by 김현욱 on 2023/05/27.
//

#include <QTableWidget>
#include "MyStock.h"
#include "../../components/SearchInput.h"

MyStock::MyStock(QWidget *parent) : QWidget(parent){
    initUi();
}

void MyStock::initUi() {

    QTableWidget* table = new QTableWidget(3, 2); // 3행 2열의 표를 생성

    QTableWidgetItem *item1 = new QTableWidgetItem("Cell 1");
    QTableWidgetItem *item2 = new QTableWidgetItem("Cell 2");
    QTableWidgetItem *item3 = new QTableWidgetItem("Cell 3");
    QTableWidgetItem *item4 = new QTableWidgetItem("Cell 4");
    QTableWidgetItem *item5 = new QTableWidgetItem("Cell 5");
    QTableWidgetItem *item6 = new QTableWidgetItem("Cell 6");

    table->setItem(0, 0, item1); // (0, 0) 위치에 아이템 설정
    table->setItem(0, 1, item2); // (0, 1) 위치에 아이템 설정
    table->setItem(1, 0, item3); // (1, 0) 위치에 아이템 설정
    table->setItem(1, 1, item4); // (1, 1) 위치에 아이템 설정
    table->setItem(2, 0, item5); // (2, 0) 위치에 아이템 설정
    table->setItem(2, 1, item6); // (2, 1) 위치에 아이템 설정

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLineEdit* companyName = new QLineEdit();
    QLineEdit* companyCode = new QLineEdit();
    SearchInput *all = new SearchInput(this, new QLabel("전체 조회"), nullptr); // 종목코드 검색
    SearchInput *searchingCompanyName = new SearchInput(this, new QLabel("회사명"), companyName); // 회사명 검색
    SearchInput *searchingCompanyCode = new SearchInput(this, new QLabel("종목코드"), companyCode); // 종목코드 검색
    mainLayout->addWidget(all);
    mainLayout->addWidget(searchingCompanyName);
    mainLayout->addWidget(searchingCompanyCode);
    mainLayout->addWidget(table);

    mainLayout->setSpacing(0);

    setLayout(mainLayout);
}