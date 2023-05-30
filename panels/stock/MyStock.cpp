//
// Created by 김현욱 on 2023/05/27.
//

#include <QTableWidget>
#include "MyStock.h"
#include "../../components/SearchInput.h"
#include "../../database/SQLController.h"
#include "../../constants/type/UserSearchType.cpp"

MyStock::MyStock(StockMenu *parent) : QWidget(parent){
    initUi();
    this->parent = parent;
}

void MyStock::initUi() {
    auto* list = new QStringList;
    list->push_back("종목코드");
    list->push_back("회사이름");
    list->push_back("회사이메일");
    list->push_back("회사전화번호");
    list->push_back("소유한 주식 수");
    list->push_back("받은 총 배당 금액");
    QTableWidget* table = new QTableWidget(100, 6); // 3행 2열의 표를 생성
    table->setHorizontalHeaderLabels(*list);

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
//    QPushButton::connect(all->searchButton, &QPushButton::clicked, [=](){
//        getMyStock();
//    });
    setLayout(mainLayout);
}

//void MyStock::getMyStock() {
//    string email = parent->pEdit->text().toUtf8().toStdString();
//    Member* member = SQLController::getMember(UserSearchType::EMAIL, email);
//    MyStockDto *myStock = SQLController::getMyStockList(member->memberId, 1, "1");
//    cout << myStock[0].companyCode;
//}