//
// Created by 김현욱 on 2023/05/29.
//

#include <QTableWidget>
#include "CheckingSchema.h"

using namespace std;
CheckingSchema::CheckingSchema(QWidget *parent) {
    initUi();

}
void CheckingSchema::initUi() {
    auto *searchInput = new SearchInput(this, new QLabel("검색할 스키마 이름 : "),word);
    searchInput->searchButton->connect(searchInput->searchButton,&QPushButton::clicked,[=](){
        setTableWidgetBySchema((SQLCHAR *) word->text().toStdString().c_str());
    });
    table = new QTableWidget(10,5);
    auto* list = new QStringList;
    list->push_back("컬럼이름");
    list->push_back("컬럼이름 길이");
    list->push_back("컬럼 데이터 사이즈");
    list->push_back("nullable");
    list->push_back("데이터 타입");
    table->setHorizontalHeaderLabels(*list);
    auto* mainLayout = new QVBoxLayout();
    backButton->setFixedSize(100,25);
    mainLayout->addWidget(backButton);
    mainLayout->addWidget(searchInput);
    mainLayout->addWidget(table);
    setLayout(mainLayout);
}

// 스키마 이름을 받아서 테이블 위젯에 뿌려주는 함수
void CheckingSchema::setTableWidgetBySchema(SQLCHAR *target) {
    Schema *schema = SQLController::getSchema((SQLCHAR *) target);
    int i = 0;
    table->clearContents();
    while (schema[i].columnName != nullptr) {
        table->setItem(i, 0, new QTableWidgetItem((char *) schema[i].columnName));
        table->setItem(i, 1, new QTableWidgetItem(to_string(schema[i].columnNameLen).c_str()));
        table->setItem(i, 2, new QTableWidgetItem(to_string(schema[i].columDataSize).c_str()));
        table->setItem(i, 3, new QTableWidgetItem(to_string(schema[i].nullable).c_str()));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromUtf8(schema[i].dataType)));
        i++;
    }
}
