//
// Created by 김현욱 on 2023/05/28.
//

#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include "interestingCompany.h"
#include "../../components/SearchInput.h"
#include "../../database/SQLController.h"
#include "../../constants/type/CompanySearchType.cpp"

interestingCompany::interestingCompany(StockMenu *parent) {
    this->parent = parent;
    initUi();
}

void interestingCompany::initUi() {
    auto* list = new QStringList;
    list->push_back("종목코드");
    list->push_back("회사이름");
    list->push_back("이메일");
    list->push_back("전화번호");
    list->push_back("총 발행 주식 수");
    table = new QTableWidget(100, 6); // 3행 2열의 표를 생성
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

    QPushButton::connect(all->searchButton, &QPushButton::clicked, [=](){
        setTableWidgetByCompanyList(CompanySearchType::ALL, "");
    });
    QPushButton::connect(searchingCompanyCode->searchButton, &QPushButton::clicked, [=](){
        setTableWidgetByCompanyList(CompanySearchType::COMPANY_CODE, companyCode->text().toUtf8().toStdString());
    });
    QPushButton::connect(searchingCompanyName->searchButton, &QPushButton::clicked, [=](){
        setTableWidgetByCompanyList(CompanySearchType::NAME, companyName->text().toUtf8().toStdString());
    });

    setLayout(mainLayout);
}

void interestingCompany::setTableWidgetByCompanyList(int type, string word) {
    string email = parent->pEdit->text().toUtf8().toStdString();
    if(email.empty()) return;
    auto companyList = SQLController::getInterestingCompanyList(email, type, word);
    int i = 0;
    table->clearContents();

    while (companyList[i].companyCode != "-1") {
        QTableWidgetItem* item = new QTableWidgetItem();
        QPushButton* button = new QPushButton("관심종목 삭제");
        QPushButton::connect(button, &QPushButton::clicked, [=](){
            SQLController::deleteInterestingCompany(email, companyList[i].companyCode);
            setTableWidgetByCompanyList(type, word);
        });
        table->setItem(i, 0, new QTableWidgetItem(companyList[i].companyCode.c_str()));
        table->setItem(i, 1, new QTableWidgetItem(companyList[i].name.c_str()));
        table->setItem(i, 2, new QTableWidgetItem(companyList[i].email.c_str()));
        table->setItem(i, 3, new QTableWidgetItem(companyList[i].phone.c_str()));
        QString SHARES = QString::fromStdString(to_string(companyList[i].shares));
        table->setItem(i, 4, new QTableWidgetItem(SHARES));
        table->setItem(i,5,item);
        table->setCellWidget(i,5,button);
        i++;
    }
}