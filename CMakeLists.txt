cmake_minimum_required(VERSION 3.24)
project(stock_qt_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH /Users/wook/Development/qt/6.4.2/macos/lib/cmake)

find_package(ODBC REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(stock_qt_project main.cpp mainWindow.cpp mainWindow.cpp mainWindow.h panels/user/SignUp.cpp panels/user/SignUp.h panels/user/Following.cpp panels/user/Following.h panels/user/Account.cpp panels/user/Account.h panels/MainMenu.cpp panels/MainMenu.h components/MenuButton.cpp components/MenuButton.h panels/stock/MyStock.cpp panels/stock/MyStock.h panels/stock/Dividend.cpp panels/stock/Dividend.h panels/StockMenu.cpp panels/StockMenu.h components/SearchInput.cpp components/SearchInput.h panels/interesting/interestingCompany.cpp panels/interesting/interestingCompany.h database/databaseConnection.cpp database/databaseConnection.h database/DBExceptionHandler.cpp database/DBExceptionHandler.h database/SQLController.cpp database/SQLController.h panels/schmas/CheckingSchema.cpp panels/schmas/CheckingSchema.h database/dto/Schema.cpp panels/interesting/AddingInterestingCompany.cpp panels/interesting/AddingInterestingCompany.h database/dto/Company.cpp database/dto/Address.cpp constants/type/CompanySearchType.cpp components/ButtonWidgetItem.cpp components/ButtonWidgetItem.h constants/type/UserSearchType.cpp database/dto/Member.cpp panels/UserMenu.cpp panels/UserMenu.h panels/user/Withdrawal.cpp panels/user/Withdrawal.h database/dto/MyStock.cpp)

target_link_libraries(stock_qt_project ODBC::ODBC)
target_link_libraries(stock_qt_project
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

