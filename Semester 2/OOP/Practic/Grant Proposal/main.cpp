#include <QApplication>
#include "service.h"
#include "gui.h"
#include <vector>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    FileRepo repo("researchers.txt", "ideas.txt");
    Service service(repo);
    std::vector<ResearcherWindow*> windows;
    for (const auto& r : service.getResearchers()) {
        auto* w = new ResearcherWindow(service, r);
        w->show();
        windows.push_back(w);
    }
    return app.exec();
}
