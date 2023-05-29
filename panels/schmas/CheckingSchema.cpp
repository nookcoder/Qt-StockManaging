//
// Created by 김현욱 on 2023/05/29.
//

#include <QTableWidget>
#include "CheckingSchema.h"

using namespace std;
CheckingSchema::CheckingSchema(QWidget *parent) {

}
void CheckingSchema::initUi() {
//    Schema* schemas;
//    SQLController::getSchema((SQLCHAR *) "COMPANY");
//    for (int i =0; i<10; i++) {
//        cout << schemas[i].columnName << endl;
//        cout << schemas[i].columnNameLen << endl;
//        cout << schemas[i].columDataSize << endl;
//        cout << schemas[i].decimalDigits << endl;
//        cout << schemas[i].nullable << endl;
//    }
    QTableWidget *table = new QTableWidget(10,7);
}
