//
// Created by 김현욱 on 2023/05/27.
//

#include <QLineEdit>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTableWidget>
#include "Following.h"
#include "../../components/SearchInput.h"

Following::Following(QWidget *parent) : QWidget(parent){
    initUi();
}

void Following::initUi() {
    // 메인 컴포넌트
    QTableWidget* table = new QTableWidget(3, 2); // 3행 2열의 표를 생성

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLineEdit* companyName = new QLineEdit();
    QLineEdit* companyCode = new QLineEdit();
    SearchInput *searchingCompanyName = new SearchInput(this, new QLabel("사용자_NO"), companyName); // 회사명 검색
    SearchInput *searchingCompanyCode = new SearchInput(this, new QLabel("이메일"), companyCode); // 종목코드 검색
    mainLayout->addWidget(searchingCompanyName);
    mainLayout->addWidget(searchingCompanyCode);
    mainLayout->addWidget(table);

    mainLayout->setSpacing(0);

    setLayout(mainLayout);
}
