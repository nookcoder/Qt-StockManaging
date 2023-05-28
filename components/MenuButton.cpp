#include <QPushButton>
#include "MenuButton.h"

//
// Created by 김현욱 on 2023/05/27.
//
MenuButton::MenuButton(QWidget *parent, QString buttonText) : QPushButton(buttonText, parent) {
    setFixedSize(200,50); // 버튼의 크기를 고정시킨다.
}