//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_DBEXCEPTIONHANDLER_H
#define STOCK_QT_PROJECT_DBEXCEPTIONHANDLER_H

#include "sql.h"
#include "sqlext.h"
#include "iostream"
class DBExceptionHandler {
public:
    static int handle(SQLRETURN retcode);
    static void HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, SQLRETURN retCode);
};


#endif //STOCK_QT_PROJECT_DBEXCEPTIONHANDLER_H
