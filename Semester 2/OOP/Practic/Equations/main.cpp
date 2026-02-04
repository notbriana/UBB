#include <QtWidgets/QApplication>
#include "gui_equation.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    GuiEquation window;
    window.show();

    return app.exec();
}