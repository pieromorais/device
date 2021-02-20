#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QLabel>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QLabel label;

    label.setText("Simplesmente demais!");
    label.show();
    
    return app.exec();
}