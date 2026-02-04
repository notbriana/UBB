#include <QApplication>
#include "service.h"
#include "gui.h"
#include "filerepo.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    FileRepo repo("questions.txt", "participants.txt");
    Service service(repo);
    service.load();

    PresenterWindow* presenter = new PresenterWindow(service);
    presenter->show();

    std::vector<ParticipantWindow*> participantWindows;
    for (const auto& p : service.getParticipants()) {
        auto* w = new ParticipantWindow(service, p.getName());
        w->show();
        participantWindows.push_back(w);
    }

    int ret = app.exec();
    service.save();
    return ret;
}
