#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"
#include <vector>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    FileRepo repo("users.txt", "items.txt");
    AuctionService service(repo);

    const auto& users = service.getUsers();
    std::vector<AuctionGUI*> windows;

    // Create a window for each user
    for (const auto& user : users) {
        auto* gui = new AuctionGUI(service, user.id);
        gui->setWindowTitle(QString::fromStdString("Auction - " + user.name));
        gui->show();
        windows.push_back(gui);
    }

    int result = app.exec();

    // Clean up windows
    for (auto* gui : windows) {
        delete gui;
    }

    service.saveAll();
    return result;
}