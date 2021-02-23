#include "MainWindow.h"

#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QLabel>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    MainWindow main_window;

    main_window.show();
    
    return app.exec();
}