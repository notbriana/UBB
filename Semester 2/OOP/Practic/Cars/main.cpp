#include "gui_car.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GuiCar w;
    w.show();
    return a.exec();
}