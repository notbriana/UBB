#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    FileRepo repo("programmers.txt", "tasks.txt");
    Service service(repo);
    std::vector<Programmer> programmers = repo.loadProgrammers();

    std::vector<std::unique_ptr<ProgrammerWindow>> windows;
    for (const auto& p : programmers) {
        windows.emplace_back(new ProgrammerWindow(p, service));
        windows.back()->show();
    }

    int result = app.exec();
    service.save();
    return result;
}
