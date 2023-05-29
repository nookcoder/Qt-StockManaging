//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_SQLCONTROLLER_H
#define STOCK_QT_PROJECT_SQLCONTROLLER_H

#include <sqltypes.h>
#include "sql.h"
#include "iostream"
#include "./dto/Schema.cpp"
#include "./dto/Company.cpp"
#include "./dto/Member.cpp"
#include "./dto/Address.cpp"
class SQLController {
public:
    static std::string get_data_type_in_string(SQLSMALLINT i);

    static Schema* getSchema(SQLCHAR *schemaName);
    static Company* getCompanyList(int searchType, string value);

    static Member* getMember(int searchType, string value);
    static void addMember(Member* member, Address* address);
    static SQLINTEGER addAddress(Address* address);
    static Company* getInterestingCompanyList(string userEmail, int type, string value);

    static void addInterestingCompany(const string& userEmail, string companyCode);

    static void deleteInterestingCompany(const string& userEmail, string companyCode);

};


#endif //STOCK_QT_PROJECT_SQLC
// ONTROLLER_H
