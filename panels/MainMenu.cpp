//
// Created by 김현욱 on 2023/05/27.
//

#include <QLabel>
#include <QVBoxLayout>
#include "MainMenu.h"

MainMenu::MainMenu(QMainWindow *parent, SQLController *sqlController) {
    initUi();
}
void MainMenu::initUi() {
    QLabel* label = new QLabel("사용자 메뉴");
    label->setAlignment(Qt::AlignCenter);
    label->setMargin(50);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addWidget(schemasButton);
    layout->addWidget(signUpButton);
    layout->addWidget(stockButton);
    this->setLayout(layout);
}

void MainMenu::turnPanel(QWidget *oldWidget, QWidget *newWidget) {
    oldWidget->hide();
    newWidget->show();
}

