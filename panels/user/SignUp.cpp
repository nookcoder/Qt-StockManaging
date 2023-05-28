//
// Created by 김현욱 on 2023/05/27.
//

#include "SignUp.h"

SignUp::SignUp(mainWindow *parent) {
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
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(signUpButton);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(phoneLayout);
    mainLayout->addLayout(siLayout);
    mainLayout->addLayout(dongLayout);
    mainLayout->addLayout(detailAddressLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void SignUp::bindButtonEvent(mainWindow *parent) {
//    QPushButton::connect(backButton, &QPushButton::clicked, [&parent](){
//        parent->backToUserMenu();
//    });
}