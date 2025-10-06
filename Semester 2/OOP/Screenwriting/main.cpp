#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    FileRepo repo("writers.txt", "ideas.txt");
    repo.load();
    Service srv(repo);
    std::vector<WriterWindow*> windows;
    for (const auto& w : srv.getWriters()) {
        auto* win = new WriterWindow(srv, w);
        win->show();
        windows.push_back(win);
    }
    return a.exec();
}