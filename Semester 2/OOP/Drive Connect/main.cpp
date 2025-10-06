#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    FileRepo repo("drivers.txt", "reports.txt");
    auto drivers = repo.loadDrivers();
    auto reports = repo.loadReports();
    Service service(repo, drivers, reports);

    std::vector<DriverWindow*> driverWindows;
    for (const auto& d : drivers) {
        auto* w = new DriverWindow(service, d);
        w->show();
        driverWindows.push_back(w);
    }
    MapWindow mapWin(service);
    mapWin.show();

    int result = app.exec();
    service.saveReports(repo);
    return result;
}
