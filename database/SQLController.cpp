//
// Created by 김현욱 on 2023/05/29.
//

#include "SQLController.h"
#include "databaseConnection.h"
#include "iostream"

using namespace std;
void SQLController::getSchema(SQLCHAR *schemaName, Schema *schema[50]) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[101];
        SQLSMALLINT numCols = -1;// number of columns
        SQLCHAR columnName[50][31];
        SQLSMALLINT columnNameLen[50];
        SQLSMALLINT columnDataType[50];
        SQLULEN columnDataSize[50];
        SQLSMALLINT columnDataDecimalDigits[50];
        SQLSMALLINT columnDataNullable[50];
        SQLCHAR tables[50][50];
        snprintf((char *) query, 101, "SELECT * FROM %s", schemaName);
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        SQLNumResultCols(databaseConnection::hstmt, &numCols);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
            return;
        }
        for (int i = 0; i < numCols; ++i) {
            SQLDescribeCol(databaseConnection::hstmt, i + 1, columnName[i], 30, &columnNameLen[i],
                           &columnDataType[i],
                           &columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);
            schema[i]->columnName = columnName[i];
            schema[i]->columnNameLen = columnNameLen[i];
            schema[i]->dataType = get_data_type_in_string(columnDataType[i]);
            schema[i]->columDataSize = columnDataSize[i];
            schema[i]->decimalDigits = columnDataDecimalDigits[i];
            schema[i]->nullable = columnDataNullable[i];
        }
        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        return;
    } else {
        cout << "ERROR" << endl;
        return;
    }
}

string SQLController::get_data_type_in_string(SQLSMALLINT i) {
    switch (i) {
        case SQL_CHAR:
            return "CHAR";
        case SQL_VARCHAR:
            return "VARCHAR";
        case SQL_LONGVARCHAR:
            return "LONGVARCHAR";
        case SQL_WCHAR:
            return "WCHAR";
        case SQL_WVARCHAR:
            return "WVARCHAR";
        case SQL_WLONGVARCHAR:
            return "WLONGVARCHAR";
        case SQL_NUMERIC:
            return "NUMERIC";
        case SQL_SMALLINT:
            return "SMALLINT";
        case SQL_INTEGER:
            return "INTEGER";
        case SQL_REAL:
            return "REAL";
        case SQL_FLOAT:
            return "FLOAT";
        case SQL_DOUBLE:
            return "DOUBLE";
        case SQL_BIT:
            return "BIT";
        case SQL_TINYINT:
            return "TINYINT";
        case SQL_BIGINT:
            return "BIGINT";
        case SQL_BINARY:
            return "BINARY";
        case SQL_VARBINARY:
            return "VARBINARY";
        case SQL_LONGVARBINARY:
            return "LONGVARBINARY";
        case SQL_TYPE_DATE:
            return "TYPE_DATE";
        case SQL_TYPE_TIME:
            return "TYPE_TIME";
        case SQL_TYPE_TIMESTAMP:
            return "TYPE_TIMESTAMP";
        case SQL_INTERVAL_MONTH:
            return "INTERVAL_MONTH";
        case SQL_INTERVAL_YEAR:
            return "INTERVAL_YEAR";
        case SQL_INTERVAL_YEAR_TO_MONTH:
            return "INTERVAL_YEAR_TO_MONTH";
        case SQL_INTERVAL_DAY:
            return "INTERVAL_DAY";
        case SQL_INTERVAL_HOUR:
            return "INTERVAL_HOUR";
        case SQL_INTERVAL_MINUTE:
            return "INTERVAL_MINUTE";
        case SQL_INTERVAL_SECOND:
            return "INTERVAL_SECOND";
        case SQL_INTERVAL_DAY_TO_HOUR:
            return "INTERVAL_DAY_TO_HOUR";
        case SQL_INTERVAL_DAY_TO_MINUTE:
            return "INTERVAL_DAY_TO_MINUTE";
        case SQL_INTERVAL_DAY_TO_SECOND:
            return "INTERVAL_DAY_TO_SECOND";
        case SQL_INTERVAL_HOUR_TO_MINUTE:
            return "INTERVAL_HOUR_TO_MINUTE";
        case SQL_INTERVAL_HOUR_TO_SECOND:
            return "INTERVAL_HOUR_TO_SECOND";
        case SQL_INTERVAL_MINUTE_TO_SECOND:
            return "INTERVAL_MINUTE_TO_SECOND";
        case SQL_GUID:
            return "GUID";
        default:
            return "UNKNOWN";
    }
}

Schema* SQLController::getSchema(SQLCHAR *schemaName) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        Schema schema[50];
        SQLCHAR query[101];
        SQLSMALLINT numCols = -1;// number of columns
        SQLCHAR columnName[50][31];
        SQLSMALLINT columnNameLen[50];
        SQLSMALLINT columnDataType[50];
        SQLULEN columnDataSize[50];
        SQLSMALLINT columnDataDecimalDigits[50];
        SQLSMALLINT columnDataNullable[50];
        SQLCHAR tables[50][50];
        snprintf((char *) query, 101, "SELECT * FROM %s", schemaName);
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        SQLNumResultCols(databaseConnection::hstmt, &numCols);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
            return nullptr;
        }
        int i;
        for (i = 0; i < numCols; ++i) {
            SQLDescribeCol(databaseConnection::hstmt, i + 1, columnName[i], 30, &columnNameLen[i],
                           &columnDataType[i],
                           &columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);
            schema[i].columnName = columnName[i];
            schema[i].columnNameLen = columnNameLen[i];
            schema[i].dataType = get_data_type_in_string(columnDataType[i]);
            schema[i].columDataSize = columnDataSize[i];
            schema[i].decimalDigits = columnDataDecimalDigits[i];
            schema[i].nullable = columnDataNullable[i];
        }
        schema[i].columnName = nullptr;
        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        return schema;
    }
}
