//
// Created by 김현욱 on 2023/05/27.
//

#include "SearchInput.h"

SearchInput::SearchInput(QWidget *parent, QLabel* title, QLineEdit *lineEdit, QString buttonName) : QWidget(parent) {
    QHBoxLayout *leftLayout = new QHBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    if(lineEdit != nullptr){
        lineEdit->setFixedSize(200, 30);
    }
    if(buttonName != nullptr){
        searchButton = new QPushButton(buttonName);
    }
    leftLayout->addWidget(title);
    leftLayout->addWidget(lineEdit);
    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(searchButton);
    setLayout(mainLayout);
}

