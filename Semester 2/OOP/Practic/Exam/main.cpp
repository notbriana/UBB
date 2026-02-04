#include "service.h"
#include "gui.h"
#include <QApplication>
#include <vector>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    FileRepo repo("departments.txt", "volunteers.txt");
    Service service(repo);
    std::vector<DepartementWindow*> DepartementWindows;
    for (const auto& d : service.getDepartments()) {
        DepartementWindow* win = new DepartementWindow(service, d);
        win->show();
        DepartementWindows.push_back(win);
    }
    StatisticWindow statisticsWindow(service);
    statisticsWindow.show();
    int result = app.exec();
    service.save();
    for (auto* win : DepartementWindows) {
        delete win;
    }
    return result;
}
