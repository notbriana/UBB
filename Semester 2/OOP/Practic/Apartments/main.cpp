#include <QApplication>
#include "gui_apartment.h"
#include "repository.h"
#include "service.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Repository repo;
    Service service(repo);
    GuiApartments gui(service);
    gui.show();
    return app.exec();
}
