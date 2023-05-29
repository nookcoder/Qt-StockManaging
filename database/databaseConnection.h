//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_DATABASECONNECTION_H
#define STOCK_QT_PROJECT_DATABASECONNECTION_H

#include "sql.h"
#include "sqlext.h"
#include "DBExceptionHandler.h"

class databaseConnection {
public:
    explicit databaseConnection();
    static SQLHENV henv;
    static SQLHDBC hdbc;
    static SQLHSTMT hstmt;
    static SQLRETURN retcode;

    static SQLRETURN connect();
    static void disconnect();
    static void checkSchema();

    static char *get_data_type_in_string(SQLSMALLINT i);
private:
};


#endif //STOCK_QT_PROJECT_DATABASECONNECTION_H
