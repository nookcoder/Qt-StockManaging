//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_SQLCONTROLLER_H
#define STOCK_QT_PROJECT_SQLCONTROLLER_H

#include <sqltypes.h>
#include "sql.h"
#include "iostream"
#include "./dto/Schema.cpp"
class SQLController {
public:
    static void getSchema(SQLCHAR *schemaName, Schema* schema[50]);
    static Schema* getSchema(SQLCHAR *schemaName);
    static std::string get_data_type_in_string(SQLSMALLINT i);
};


#endif //STOCK_QT_PROJECT_SQLC
// ONTROLLER_H
