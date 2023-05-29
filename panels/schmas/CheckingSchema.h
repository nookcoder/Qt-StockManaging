//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_CHECKINGSCHEMA_H
#define STOCK_QT_PROJECT_CHECKINGSCHEMA_H


#include <QWidget>
#include "../../database/SQLController.h"
#include "iostream"

class CheckingSchema : public QWidget{
public:
    explicit CheckingSchema(QWidget *parent = nullptr);
private:
    void initUi();
};


#endif //STOCK_QT_PROJECT_CHECKINGSCHEMA_H
