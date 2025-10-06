#include <QApplication>
#include "gui.h"
#include "filerepo.h"
#include "service.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    FileRepo repo("drivers.txt", "reports.txt");
    // FileRepo loads data in its constructor, no need for explicit load
    Service service(repo);

    // Open Map Window
    MapWindow* mapWin = new MapWindow(&service);
    mapWin->show();

    // Create a window for each driver
    for (const auto& driver : service.getAllDrivers()) {
        DriverWindow* win = new DriverWindow(driver, &service);
        win->show();
    }

    int result = a.exec();

    service.saveAll(); // Save before exiting
    return result;
}
