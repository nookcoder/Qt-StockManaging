//
// Created by 김현욱 on 2023/05/27.
//

#ifndef STOCK_QT_PROJECT_SIGNUP_H
#define STOCK_QT_PROJECT_SIGNUP_H

#include <QLabel>
#include <QPushButton>
#include "../../mainWindow.h"
#include "QLineEdit"
class SignUp: public QWidget {
public:
    explicit SignUp(mainWindow *parent = nullptr);
    QPushButton *backButton = new QPushButton("뒤로가기");

private:
    QLabel* name = new QLabel("이름 : ");
    QLabel* email = new QLabel("이메일 : ");
    QLabel* phone = new QLabel("전화번호 : ");
    QLabel* si = new QLabel("시/도 : ");
    QLabel* dong = new QLabel("동/면/읍 : ");
    QLabel* detailAddress = new QLabel("상세주소 : ");

    QLineEdit *nameLine = new QLineEdit();
    QLineEdit *emailLine = new QLineEdit();
    QLineEdit *phoneLine = new QLineEdit();
    QLineEdit *siLine = new QLineEdit();
    QLineEdit *dongLine = new QLineEdit();
    QLineEdit *detailAddressLine = new QLineEdit();

    QPushButton *signUpButton = new QPushButton("회원가입");

    QHBoxLayout *nameLayout = new QHBoxLayout();
    QHBoxLayout *emailLayout = new QHBoxLayout();
    QHBoxLayout *phoneLayout = new QHBoxLayout();
    QHBoxLayout *siLayout = new QHBoxLayout();
    QHBoxLayout *dongLayout = new QHBoxLayout();
    QHBoxLayout *detailAddressLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    void initUi();
    void bindButtonEvent(mainWindow *parent);
};


#endif //STOCK_QT_PROJECT_SIGNUP_H
