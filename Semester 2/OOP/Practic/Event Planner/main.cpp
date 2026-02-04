#include <QApplication>
#include "Service.h"
#include "FileRepo.h"
#include "GUI.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Adjust file names as needed
    FileRepo repo("events.txt", "people.txt");
    Service service(repo);
    service.load();

    // Create a window for each person
    std::vector<PersonWindow*> personWindows;
    for (const auto& person : service.getPeople()) {
        PersonWindow* win = new PersonWindow(service, person);
        win->show();
        personWindows.push_back(win);
    }

    // Create and show the popular events window
    PopularEventsWindow* popWin = new PopularEventsWindow(service);
    popWin->show();

    int result = app.exec();

    service.save();
    return result;
}
