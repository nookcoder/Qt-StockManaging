//
// Created by 김현욱 on 2023/05/29.
//

#include "DBExceptionHandler.h"
#include "iostream"
using namespace std;
int DBExceptionHandler::handle(SQLRETURN retcode) {
    if(retcode != SQL_ERROR && retcode != SQL_NO_DATA) {
        cout << "SQL ERROR";
        cout << retcode << endl;
        return 0;
    }

    return -1;
}

void DBExceptionHandler::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, SQLRETURN retCode) {
    SQLINTEGER i = 1;
    SQLCHAR sqlState[6];
    SQLINTEGER nativeError;
    SQLCHAR messageText[256];
    SQLSMALLINT textLength;

    while (SQLGetDiagRec(hType, hHandle, i, sqlState, &nativeError, messageText, sizeof(messageText), &textLength) == SQL_SUCCESS) {
        std::cout << "SQLSTATE: " << sqlState << std::endl;
        std::cout << "Native Error Code: " << nativeError << std::endl;
        std::cout << "Error Message: " << messageText << std::endl;
        i++;
    }
}
