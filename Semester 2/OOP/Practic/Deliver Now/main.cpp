#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    FileRepo repo("couriers.txt", "packages.txt");
    Service service(repo);

    // Open the company window (only once)
    GUI companyWindow(service);
    service.addObserver(&companyWindow);
    companyWindow.start();

    // Open a window for each courier
    std::vector<QDialog*> courierDialogs;
    for (const auto& courier : service.getCouriers()) {
        // Each courier window is a QDialog created by companyWindow
        companyWindow.openCourierWindow(courier);
        // The dialog is managed inside companyWindow.courierWindows
    }

    int result = a.exec();
    service.saveToFile();
    return result;
}
