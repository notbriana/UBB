#include <QApplication>
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    FileRepo repo("doctors.txt", "patients.txt");
    Service service(repo);
    std::vector<DoctorWindow*> windows;
    for (const auto& doc : service.getDoctors()) {
        auto* win = new DoctorWindow(service, doc);
        win->show();
        windows.push_back(win);
    }
    StatsWindow stats(service);
    stats.show();
    int ret = app.exec();
    service.save();
    return ret;
}
