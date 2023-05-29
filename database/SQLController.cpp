//
// Created by 김현욱 on 2023/05/29.
//

#include "SQLController.h"
#include "databaseConnection.h"
#include "../constants/type/CompanySearchType.cpp"
#include "../constants/type/UserSearchType.cpp"
#include "string"

using namespace std;

Schema *SQLController::getSchema(SQLCHAR *schemaName) {
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
        databaseConnection::disconnect();
        return schema;
    }
}

Company *SQLController::getCompanyList(int searchType, string value) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR companyCode[20];
        SQLCHAR name[50];
        SQLCHAR email[50];
        SQLCHAR phone[20];
        SQLBIGINT shares;
        SQLINTEGER address;
        SQLLEN indicator;
        SQLCHAR query[101];

        switch (searchType) {
            case CompanySearchType::COMPANY_CODE:
                snprintf((char *) query, 101, "SELECT * FROM company WHERE COMPANY_CODE = '%s'", value.c_str());
                break;
            case CompanySearchType::NAME:
//                snprintf((char *) query, 101, "SELECT * FROM company WHERE NAME LIKE '%s%s%s'", "%",value.c_str(),"%");
                snprintf((char *) query, 101, "SELECT * FROM company WHERE NAME LIKE '%%%s%%'", value.c_str());
                cout << query;
                break;
            default:
                snprintf((char *) query, 101, "SELECT * FROM company");
                break;
        }
//        snprintf((char *) query, 101, "SELECT * FROM company");
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
            return nullptr;
        }
        Company *company = new Company[50];
        SQLBindCol(databaseConnection::hstmt, 1, SQL_C_CHAR, companyCode, 20, nullptr);
        SQLBindCol(databaseConnection::hstmt, 2, SQL_C_CHAR, name, 50, nullptr);
        SQLBindCol(databaseConnection::hstmt, 3, SQL_C_CHAR, email, 50, nullptr);
        SQLBindCol(databaseConnection::hstmt, 4, SQL_C_CHAR, phone, 20, nullptr);
        SQLBindCol(databaseConnection::hstmt, 5, SQL_C_SBIGINT, &shares, sizeof(shares), nullptr);
        SQLBindCol(databaseConnection::hstmt, 6, SQL_C_SLONG, &address, 0, &indicator);

        int i = 0;
        while (SQLFetch(databaseConnection::hstmt) != SQL_NO_DATA) {
            string sCompanyCode = string((char *) companyCode);
            string sName = string((char *) name);
            string sEmail = string((char *) email);
            string sPhone = string((char *) phone);
            company[i].name = sName;
            company[i].email = sEmail;
            company[i].companyCode = sCompanyCode;
            company[i].phone = sPhone;
            company[i].shares = shares;
            company[i].address = address;
            i++;
        }
        company[i].companyCode = "-1";

        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        databaseConnection::disconnect();
        return company;
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

Member *SQLController::getMember(int searchType, string value) {
    SQLCHAR query[101];
    switch (searchType) {
        case UserSearchType::EMAIL:
            snprintf((char *) query, 101, "SELECT * FROM MEMBER WHERE EMAIL = '%s'", value.c_str());
            break;
        case UserSearchType::NAME:
            snprintf((char *) query, 101, "SELECT * FROM MEMBER WHERE NAME = '%s'", value.c_str());
            break;
        case UserSearchType::PHONE:
            snprintf((char *) query, 101, "SELECT * FROM MEMBER WHERE PHONE = '%s'", value.c_str());
            break;
        case UserSearchType::ALL:
            snprintf((char *) query, 101, "SELECT * FROM MEMBER");
            break;
    }
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
            return nullptr;
        }
        Member *member = new Member[100];
        SQLCHAR email[50], name[50], phone[11];
        SQLINTEGER memberNo, addressId, accountId;
        SQLBindCol(databaseConnection::hstmt, 1, SQL_C_LONG, &memberNo, 0, nullptr);
        SQLBindCol(databaseConnection::hstmt, 2, SQL_C_CHAR, name, 50, nullptr);
        SQLBindCol(databaseConnection::hstmt, 3, SQL_C_CHAR, phone, 50, nullptr);
        SQLBindCol(databaseConnection::hstmt, 4, SQL_C_CHAR, email, 20, nullptr);
        SQLBindCol(databaseConnection::hstmt, 5, SQL_C_LONG, &addressId, 0, nullptr);
        SQLBindCol(databaseConnection::hstmt, 5, SQL_C_LONG, &accountId, 0, nullptr);

        int i = 0;
        while (SQLFetch(databaseConnection::hstmt) != SQL_NO_DATA) {
            cout << "Member No: " << memberNo << "Member Name: " << name << "Member Phone: " << phone
                 << "Member Email: " << email << "Member Address Id: " << addressId << "Member Account Id: " << accountId
                 << endl;
            string sEmail = (char *) email;
            string sPhone = (char *) phone;
            string sName = (char *) name;
            member[i].memberId = memberNo;
            member[i].addressId = addressId;
            member[i].accountId = accountId;
            member[i].email = sEmail;
            member[i].name = sName;
            member[i].phone = sPhone;
            i++;
        }
        member[i].email = "-1";
        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        databaseConnection::disconnect();
        return member;
    }
}

void SQLController::addInterestingCompany(const string &userEmail, string companyCode) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[101];
        Member* member = getMember(UserSearchType::EMAIL, userEmail);
        databaseConnection::connect();
        snprintf((char *) query, 101, "INSERT INTO INTERESING(MEMBER, COMPANY) VALUES (%d,'%s')", member[0].memberId, companyCode.c_str());
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
            return;
        }

        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        databaseConnection::disconnect();
    }
}
