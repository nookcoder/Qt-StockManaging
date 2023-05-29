//
// Created by 김현욱 on 2023/05/29.
//
#include "sql.h"
#include "iostream"

class Schema {
public:
    unsigned char *columnName;
    SQLSMALLINT columnNameLen;
    std::string dataType;
    SQLULEN columDataSize;
    SQLSMALLINT decimalDigits;
    SQLSMALLINT nullable;
};