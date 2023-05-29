//
// Created by 김현욱 on 2023/05/29.
//
#include <QString>
#include "string"
using namespace std;
class Member {
public:
    Member(){};
    Member(QString qString, QString qString1, QString qString2){
        this->name = qString.toUtf8().toStdString();
        this->phone = qString1.toUtf8().toStdString();
        this->email = qString2.toUtf8().toStdString();
    };

    int memberId;
    string name;
    string phone;
    string email;
    int addressId;
    int accountId;
};
