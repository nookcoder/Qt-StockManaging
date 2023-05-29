//
// Created by 김현욱 on 2023/05/28.
//

#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include "interestingCompany.h"
#include "../../components/SearchInput.h"

interestingCompany::interestingCompany(QWidget *parent) {
    initUi();
}

void interestingCompany::initUi() {
    QTableWidget* table = new QTableWidget(3, 2); // 3행 2열의 표를 생성

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
