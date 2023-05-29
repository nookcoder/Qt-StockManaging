//
// Created by 김현욱 on 2023/05/29.
//

#ifndef STOCK_QT_PROJECT_BUTTONWIDGETITEM_H
#define STOCK_QT_PROJECT_BUTTONWIDGETITEM_H


#include <QTableWidgetItem>
#include "QPushButton"

class ButtonWidgetItem : public QTableWidgetItem {
public:
    explicit ButtonWidgetItem(const QString& text, QWidget* parent = nullptr)
            : button(new QPushButton(text)) {
        setFlags(flags() ^ Qt::ItemIsEditable);  // 편집 불가능하도록 설정
    }

    QPushButton* getButton() const {
        return button;
    }

private:
    QPushButton* button;
};

#endif //STOCK_QT_PROJECT_BUTTONWIDGETITEM_H
