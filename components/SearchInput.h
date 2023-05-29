//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_SEARCHINPUT_H
#define STOCK_QT_PROJECT_SEARCHINPUT_H


#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

class SearchInput : public QWidget{
public:
    explicit SearchInput(QWidget* parent = nullptr, QLabel *label= nullptr, QLineEdit *lineEdit = nullptr, QString buttonName = "검색");
    QString buttonName;
    QPushButton *searchButton;
};


#endif //STOCK_QT_PROJECT_SEARCHINPUT_H
