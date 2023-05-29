//
// Created by 김현욱 on 2023/05/29.
//

#include "databaseConnection.h"
#include "iostream"
#include "format"

SQLHENV databaseConnection::henv = nullptr;
SQLHDBC databaseConnection::hdbc = nullptr;
SQLHSTMT databaseConnection::hstmt = nullptr;
SQLRETURN databaseConnection::retcode = SQL_ERROR;

using namespace std;
databaseConnection::databaseConnection() {
}

SQLRETURN databaseConnection::connect() {
    SQLRETURN retcode;
    if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv) == SQL_ERROR) {
        cout << "SQL ERROR SQL_HANDLE_ENV" << endl;
        return SQL_ERROR;
    }
    if(SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0) == SQL_ERROR) {
        cout << "SQL ERROR SQLSetEnvAttr" << endl;
        return SQL_ERROR;
    }
    if(SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc) == SQL_ERROR) {
        cout << "SQL ERROR SQL_HANDLE_DBC" << endl;
        return SQL_ERROR;
    }
    SQLCHAR *connectionString = (SQLCHAR *) "DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;DATABASE=MY_STOCK;UID=SA;PWD=Kimhw9821!";
    retcode = SQLDriverConnect(hdbc, nullptr, connectionString, SQL_NTS, nullptr, 0, nullptr, SQL_DRIVER_NOPROMPT);
    if(retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
        DBExceptionHandler::handle(retcode);
        return SQL_ERROR;
    }
    if(SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) != SQL_SUCCESS) {
        cout << "SQL ERROR SQL_HANDLE_STMT" << endl;
        return SQL_ERROR;
    }
    return SQL_SUCCESS;
}

void databaseConnection::disconnect() {
    SQLDisconnect(hdbc);					// Disconnect from the SQL Server
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);	// Free the Connection Handle
    SQLFreeHandle(SQL_HANDLE_ENV, henv);	// Free the Environment Handle
}


void databaseConnection::checkSchema() {
    if(connect() == SQL_SUCCESS) {
        SQLCHAR query[101];
        snprintf((char *) query, 101, "SELECT * FROM MEMBER");
        SQLExecDirect(hstmt, query, SQL_NTS);

        SQLCHAR empNo[100];
        SQLCHAR empName[100];

        SQLBindCol(hstmt, 1, SQL_C_CHAR, empNo, 100, NULL);
        SQLBindCol(hstmt, 2, SQL_C_CHAR, empName, 100, NULL);

        while (SQLFetch(hstmt) != SQL_NO_DATA)
        {
            cout << "empNo : " << empNo << " ";
            cout << "empName : " << empName << endl;
        }

        SQLCloseCursor(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }
    disconnect();
}

char *databaseConnection::get_data_type_in_string(SQLSMALLINT i) {
    switch (i) {
        case SQL_CHAR:
            return "CHAR";
            break;
        case SQL_VARCHAR:
            return "VARCHAR";
            break;
        case SQL_LONGVARCHAR:
            return "LONGVARCHAR";
            break;
        case SQL_WCHAR:
            return "WCHAR";
            break;
        case SQL_WVARCHAR:
            return "WVARCHAR";
            break;
        case SQL_WLONGVARCHAR:
            return "WLONGVARCHAR";
            break;
        case SQL_NUMERIC:
            return "NUMERIC";
            break;
        case SQL_SMALLINT:
            return "SMALLINT";
            break;
        case SQL_INTEGER:
            return "INTEGER";
            break;
        case SQL_REAL:
            return "REAL";
            break;
        case SQL_FLOAT:
            return "FLOAT";
            break;
        case SQL_DOUBLE:
            return "DOUBLE";
            break;
        case SQL_BIT:
            return "BIT";
            break;
        case SQL_TINYINT:
            return "TINYINT";
            break;
        case SQL_BIGINT:
            return "BIGINT";
            break;
        case SQL_BINARY:
            return "BINARY";
            break;
        case SQL_VARBINARY:
            return "VARBINARY";
            break;
        case SQL_LONGVARBINARY:
            return "LONGVARBINARY";
            break;
        case SQL_TYPE_DATE:
            return "TYPE_DATE";
            break;
        case SQL_TYPE_TIME:
            return "TYPE_TIME";
            break;
        case SQL_TYPE_TIMESTAMP:
            return "TYPE_TIMESTAMP";
            break;
        case SQL_INTERVAL_MONTH:
            return "INTERVAL_MONTH";
            break;
        case SQL_INTERVAL_YEAR:
            return "INTERVAL_YEAR";
            break;
        case SQL_INTERVAL_YEAR_TO_MONTH:
            return "INTERVAL_YEAR_TO_MONTH";
            break;
        case SQL_INTERVAL_DAY:
            return "INTERVAL_DAY";
            break;
        case SQL_INTERVAL_HOUR:
            return "INTERVAL_HOUR";
            break;
        case SQL_INTERVAL_MINUTE:
            return "INTERVAL_MINUTE";
            break;
        case SQL_INTERVAL_SECOND:
            return "INTERVAL_SECOND";
            break;
        case SQL_INTERVAL_DAY_TO_HOUR:
            return "INTERVAL_DAY_TO_HOUR";
            break;
        case SQL_INTERVAL_DAY_TO_MINUTE:
            return "INTERVAL_DAY_TO_MINUTE";
            break;
        case SQL_INTERVAL_DAY_TO_SECOND:
            return "INTERVAL_DAY_TO_SECOND";
            break;
        case SQL_INTERVAL_HOUR_TO_MINUTE:
            return "INTERVAL_HOUR_TO_MINUTE";
            break;
        case SQL_INTERVAL_HOUR_TO_SECOND:
            return "INTERVAL_HOUR_TO_SECOND";
            break;
        case SQL_INTERVAL_MINUTE_TO_SECOND:
            return "INTERVAL_MINUTE_TO_SECOND";
            break;
        case SQL_GUID:
            return "GUID";
            break;
        default:
            return "UNKNOWN";
    }
}



