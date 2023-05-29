//
// Created by 김현욱 on 2023/05/29.
//
#include <QString>
#include "string"

using namespace std;
class Address {
public:
    Address(QString qString, QString qString1, QString qString2){
        this->DO = qString.toUtf8().toStdString();
        this->DONG = qString1.toUtf8().toStdString();
        this->DETAIL = qString2.toUtf8().toStdString();
    };
    int ADDRESS_ID;
    string DONG;
    string DO;
    string DETAIL;
};