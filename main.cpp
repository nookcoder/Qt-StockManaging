#include <QApplication>
#include "mainWindow.h"
#include "database/databaseConnection.h"
#include "database/SQLController.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow *main = new mainWindow();
    Schema *pSchema = SQLController::getSchema((SQLCHAR *) "COMPANY");
    for (int i =0; i< sizeof(pSchema) && pSchema[i].columnName != nullptr; i++) {
        cout << &pSchema[i] << " ";
        cout << pSchema[i].columnName << " ";
        cout << pSchema[i].columnNameLen << " ";
        cout << pSchema[i].columDataSize << " ";
        cout << pSchema[i].decimalDigits << " ";
        cout << pSchema[i].dataType << " ";
        cout << pSchema[i].nullable << endl;
    }
    main->run();
    return QApplication::exec();
}
