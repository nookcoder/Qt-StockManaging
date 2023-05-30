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

SQLINTEGER SQLController::addAddress(Address *address) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[500];
        snprintf((char *) query, 500,
                 "INSERT INTO ADDRESS(DONG, DO, DETAIL) VALUES ('%s','%s','%s')",
                 address->DONG.c_str(), address->DO.c_str(), address->DETAIL.c_str());
        SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        if (direct != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
        }

        SQLCHAR selectQuery[101];
        snprintf((char *) selectQuery, 500,
                 "SELECT ADDRESS_ID FROM ADDRESS WHERE DONG = '%s' AND DO='%s' AND DETAIL='%s'", address->DONG.c_str(),
                 address->DO.c_str(), address->DETAIL.c_str());
        SQLRETURN direct2 = SQLExecDirect(databaseConnection::hstmt, selectQuery, SQL_NTS);
        if (direct2 != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct2);
        }

        SQLINTEGER addressId;
        int address;
        SQLBindCol(databaseConnection::hstmt, 1, SQL_C_LONG, &addressId, 0, nullptr);
        while(SQLFetch(databaseConnection::hstmt) != SQL_NO_DATA){
            address = addressId;
        }
        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        databaseConnection::disconnect();
        return address;
    }
}

void SQLController::addMember(Member *member, Address *address) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[300];
        int addressId = addAddress(address);
        databaseConnection::connect();
        cout << "ADDRESS_ID : " << addressId << endl;
        snprintf((char *) query, 300,
                 "INSERT INTO MEMBER(NAME, EMAIL, PHONE, ADDRESS) VALUES ('%s','%s','%s',%d)",
                 member->name.c_str(), member->phone.c_str(), member->email.c_str(), addressId);
        cout << "QUERY : "<< query << endl;
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


void SQLController::addInterestingCompany(const string &userEmail, string companyCode) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[101];
        Member *member = getMember(UserSearchType::EMAIL, userEmail);
        databaseConnection::connect();
        snprintf((char *) query, 101, "INSERT INTO INTERESING(MEMBER, COMPANY) VALUES (%d,'%s')",
                 member[0].memberId,
                 companyCode.c_str());
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

Company *SQLController::getInterestingCompanyList(string userEmail, int type, string value) {
    databaseConnection::connect();
    Member *member = getMember(UserSearchType::EMAIL, userEmail);
    databaseConnection::connect();
    SQLCHAR query[300];
    switch (type) {
        case CompanySearchType::ALL :
            snprintf((char *) query, 300,
                     "SELECT COMPANY_CODE, NAME, EMAIL, PHONE, SHARES FROM COMPANY AS C, INTERESING AS I WHERE I.MEMBER = '%d' AND I.COMPANY = C.COMPANY_CODE",
                     member[0].memberId);
            cout << query << endl;
            cout << "Member Id : " << member[0].memberId;
            break;
        case CompanySearchType::COMPANY_CODE :
            snprintf((char *) query, 101,
                     "SELECT C.COMPANY_CODE, C.NAME, C.EMAIL, C.PHONE, C.SHARES FROM COMPANY as C, INTERESING as I WHERE I.MEMBER = '%d' AND I.COMPANY = C.COMPANY_CODE AND C.COMPANY_CODE='%s'",
                     member[0].memberId, value.c_str());
            break;
        case CompanySearchType::NAME:
            snprintf((char *) query, 101,
                     "SELECT C.COMPANY_CODE, C.NAME, C.EMAIL, C.PHONE, C.SHARES FROM COMPANY as C, INTERESING as I WHERE I.MEMBER = '%d' AND I.COMPANY = C.COMPANY_CODE AND C.NAME='%s'",
                     member[0].memberId, value.c_str());
            break;
    }
    SQLRETURN direct = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
    if (direct != SQL_SUCCESS) {
        DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, direct);
        return nullptr;
    }

    SQLCHAR companyCode[20];
    SQLCHAR name[50];
    SQLCHAR email[50];
    SQLCHAR phone[20];
    SQLBIGINT shares;
    SQLINTEGER address;

    Company *company = new Company[50];
    SQLBindCol(databaseConnection::hstmt, 1, SQL_C_CHAR, companyCode, 20, nullptr);
    SQLBindCol(databaseConnection::hstmt, 2, SQL_C_CHAR, name, 50, nullptr);
    SQLBindCol(databaseConnection::hstmt, 3, SQL_C_CHAR, email, 50, nullptr);
    SQLBindCol(databaseConnection::hstmt, 4, SQL_C_CHAR, phone, 20, nullptr);
    SQLBindCol(databaseConnection::hstmt, 5, SQL_C_SBIGINT, &shares, sizeof(shares), nullptr);
    SQLBindCol(databaseConnection::hstmt, 6, SQL_C_SLONG, &address, 0, nullptr);

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


void SQLController::deleteInterestingCompany(const string &userEmail, string companyCode) {
    if (databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[101];
        Member *member = getMember(UserSearchType::EMAIL, userEmail);
        databaseConnection::connect();
        snprintf((char *) query, 101, "DELETE FROM INTERESING WHERE MEMBER = '%d' AND COMPANY = '%s'",
                 member[0].memberId,
                 companyCode.c_str());
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

MyStockDto *SQLController::getMyStockList(int memberId, int type, string value) {
    if(databaseConnection::connect() == SQL_SUCCESS) {
        SQLCHAR query[300];
        snprintf((char *) query, 300, "SELECT C.COMPANY_CODE, SUM(D.TOTAL_AMOUNT), SUM(S.QUANTITY)\n"
                                      "FROM SHAREHOLDER AS S, COMPANY AS C, DIVIDEND AS D \n"
                                      "WHERE S.MEMBER = %d AND S.COMPANY = C.COMPANY_CODE AND S.DIVIDEND = D.DIVIDEND_NO\n"
                                      "GROUP BY COMPANY_CODE", memberId);
        cout << query << endl;
        SQLRETURN retcode = SQLExecDirect(databaseConnection::hstmt, query, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            DBExceptionHandler::HandleDiagnosticRecord(databaseConnection::hstmt, SQL_HANDLE_STMT, retcode);
            return nullptr;
        }
        cout << "RESULT : " << retcode <<endl;
        auto *myStockDto = new MyStockDto();
        // 소유한 주식의 종목코드, 배당금 총액, 수량을 가져온다.
        SQLCHAR companyCode[30];
        SQLCHAR companyName[100];
        SQLCHAR companyEmail[100];
        SQLCHAR companyPhone[100];
        SQLINTEGER quantity;
        SQLINTEGER sum;
        SQLBindCol(databaseConnection::hstmt, 1, SQL_C_CHAR, companyCode, 30, NULL);
        SQLBindCol(databaseConnection::hstmt, 2, SQL_C_ULONG, &sum, 0, NULL);
        SQLBindCol(databaseConnection::hstmt, 3, SQL_C_ULONG, &quantity, 0, NULL);
        int i = 0;
        cout << "SQLBindCol : " <<endl;
        while(SQLFetch(databaseConnection::hstmt) != SQL_NO_DATA) {
            string code = string((char *)companyCode);
            myStockDto[i].companyCode = code;
            myStockDto[i].totalDividend = sum;
            myStockDto[i].quantity = quantity;
//            company = SQLController::getCompanyList(CompanySearchType::COMPANY_CODE, code);
//            myStockDto[i].companyName = company[0].name;
//            myStockDto[i].companyPhone = company[0].phone;
//            myStockDto[i].companyEmail = company[0].email;
            i++; // 다음 주식 정보를 가져온다.
        }

        myStockDto[i].companyCode = nullptr;

        SQLCloseCursor(databaseConnection::hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, databaseConnection::hstmt);
        databaseConnection::disconnect();
    } else {
        cout << "DB 연결 실패" << endl;
    }
}