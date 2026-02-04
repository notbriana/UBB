#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"
#include <vector>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    FileRepo repo("users.txt", "issues.txt");
    Service service(repo);

    std::vector<UserWindow*> windows;
    for (const auto& user : service.getUsers()) {
        UserWindow* w = new UserWindow(user, service);
        w->show();
        windows.push_back(w);
    }

    int ret = a.exec();
    service.save();
    return ret;
}
