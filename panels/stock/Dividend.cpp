//
// Created by 김현욱 on 2023/05/27.
//

#include <QTableWidget>
#include "Dividend.h"
#include "../../components/SearchInput.h"

Dividend::Dividend(QWidget *parent) : QWidget(parent){
    initUi();
}
void Dividend::initUi() {
    QTableWidget* table = new QTableWidget(10, 2); // 3행 2열의 표를 생성
    QLineEdit *companyName = new QLineEdit();
    QLineEdit *companyCode = new QLineEdit();
    QLineEdit *businessYear = new QLineEdit();
    SearchInput *all = new SearchInput(this, new QLabel("전체 조회"), nullptr); // 종목코드 검색
    SearchInput *searchingCompanyName = new SearchInput(this, new QLabel("회사명"), companyName); // 회사명 검색
    SearchInput *searchingCompanyCode = new SearchInput(this, new QLabel("종목코드"), companyCode); // 종목코드 검색
    SearchInput *searchingBusinessYear = new SearchInput(this, new QLabel("배당 연도"), businessYear); // 종목코드 검색
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(all);
    mainLayout->addWidget(searchingCompanyName);
    mainLayout->addWidget(searchingCompanyCode);
    mainLayout->addWidget(searchingBusinessYear);
    mainLayout->addWidget(table);
    setLayout(mainLayout);
}