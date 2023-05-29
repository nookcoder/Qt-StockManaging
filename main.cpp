#include <QApplication>
#include "mainWindow.h"
#include "database/databaseConnection.h"
#include "database/SQLController.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow *main = new mainWindow();
    main->run();
    return QApplication::exec();
}
