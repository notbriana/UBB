#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Adjust file paths as needed
    FileRepo repo("astronomers.txt", "stars.txt");
    repo.load();
    Service service(repo);

    std::vector<AstronomerWindow*> windows;
    for (const auto& astronomer : service.getAstronomers()) {
        auto* window = new AstronomerWindow(service, astronomer);
        window->setWindowTitle(QString::fromStdString(astronomer.name));
        window->show();
        windows.push_back(window);
    }

    int result = app.exec();
    service.save();
    return result;
}
