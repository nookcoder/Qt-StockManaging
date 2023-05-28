#include <QApplication>
#include <QPushButton>
#include "mainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow *main = new mainWindow();
    main->run();
    return QApplication::exec();
}
