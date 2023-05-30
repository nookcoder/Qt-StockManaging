//
// Created by 김현욱 on 2023/05/30.
//
#include <string>
using namespace std;
class MyStockDto {
public:
    string companyCode;
    string companyName;
    string companyEmail;
    string companyPhone;
    int quantity; // 보유 수량
    long totalDividend; // 총 배당금
};