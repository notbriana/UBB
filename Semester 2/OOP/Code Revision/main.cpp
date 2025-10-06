#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Repository repo;
    repo.loadProgrammers("team.txt");
    repo.loadFiles("files.txt");

    CodeRevisionService service(repo);

    std::vector<ProgrammerWindow*> windows;
    for (const auto& p : repo.getProgrammers()) {
        auto* win = new ProgrammerWindow(service, p);
        win->show();
        windows.push_back(win);
    }

    return app.exec();
}
