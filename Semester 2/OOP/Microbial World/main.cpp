#include <QApplication>
#include "service.h"
#include "gui.h"
#include "filerepo.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    FileRepo repo("biologists.txt", "bacteria.txt");
    Service service(repo);

    QVector<Biologist> biologists = service.getBiologists();
    QVector<BiologistWindow*> windows;
    for (const auto& b : biologists) {
        auto* w = new BiologistWindow(service, b);
        w->show();
        windows.append(w);
    }

    int res = app.exec();
    service.save();
    return res;
}
