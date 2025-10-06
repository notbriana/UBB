#include "service.h"
#include "gui.h"
#include <QApplication>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize file repository with the department and volunteer files
    FileRepo repo("departments.txt", "volunteers.txt");
    Service service(repo);

    // Create and show a window for each department
    std::vector<DepartmentWindow*> deptWindows;
    for (const auto& dept : service.getDepartments()) {
        DepartmentWindow* win = new DepartmentWindow(service, dept);
        win->show();
        deptWindows.push_back(win);
    }

    // Create and show the stats window
    StatsWindow statsWin(service);
    statsWin.show();

    // Run the application event loop
    int result = app.exec();

    // Save volunteers on exit
    service.save();

    // Clean up dynamically allocated windows
    for (auto* win : deptWindows) {
        delete win;
    }

    return result;
}
