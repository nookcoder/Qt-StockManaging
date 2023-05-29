//
// Created by 김현욱 on 2023/05/27.
//

#include "SignUp.h"
#include "../../database/SQLController.h"
SignUp::SignUp(QWidget *parent) {
    initUi();
//    bindButtonEvent(parent);
}

void SignUp::initUi() {
    nameLayout->addWidget(name);
    nameLayout->addWidget(nameLine);
    emailLayout->addWidget(email);
    emailLayout->addWidget(emailLine);
    phoneLayout->addWidget(phone);
    phoneLayout->addWidget(phoneLine);
    siLayout->addWidget(si);
    siLayout->addWidget(siLine);
    dongLayout->addWidget(dong);
    dongLayout->addWidget(dongLine);
    detailAddressLayout->addWidget(detailAddress);
    detailAddressLayout->addWidget(detailAddressLine);
    signUpButton->setFixedSize(200,50);
    buttonLayout->addWidget(signUpButton);
    QPushButton::connect(signUpButton, &QPushButton::clicked, this, [=](){
       Address* address = new Address(siLine->text(), dongLine->text(), detailAddressLine->text());
       Member* member = new Member(nameLine->text(), emailLine->text(), phoneLine->text());
       SQLController::addMember(member, address);
    });
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(phoneLayout);
    mainLayout->addLayout(siLayout);
    mainLayout->addLayout(dongLayout);
    mainLayout->addLayout(detailAddressLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}
