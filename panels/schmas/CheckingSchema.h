//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_CHECKINGSCHEMA_H
#define STOCK_QT_PROJECT_CHECKINGSCHEMA_H


#include <QWidget>
#include "QBoxLayout"
#include "../../database/SQLController.h"
#include "iostream"
#include "../../components/SearchInput.h"
#include "QTableWidget"
class CheckingSchema : public QWidget{
public:
    explicit CheckingSchema(QWidget *parent = nullptr);
private:
    void initUi();
    void bindEvent();
    void setTableWidgetBySchema(SQLCHAR *target);
    QLineEdit *word = new QLineEdit();
    QTableWidget* table;
};


#endif //STOCK_QT_PROJECT_CHECKINGSCHEMA_H
