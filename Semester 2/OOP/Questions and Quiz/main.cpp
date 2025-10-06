#include <QApplication>
#include "filerepo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Adjust file paths as needed
    FileRepo repo("users.txt", "questions.txt", "answers.txt");
    Service service(repo);

    // Create a window for each user
    std::vector<UserWindow*> userWindows;
    for (const auto& user : service.getUsers()) {
        UserWindow* win = new UserWindow(service, user);
        win->setWindowTitle(QString::fromStdString(user.getName()));
        win->show();
        userWindows.push_back(win);
    }

    // Create the search window
    SearchWindow* searchWin = new SearchWindow(service);
    searchWin->setWindowTitle("Search Questions");
    searchWin->show();

    int result = app.exec();

    // Save questions and answers on exit
    service.save();

    // Clean up
    for (auto* win : userWindows) delete win;
    delete searchWin;

    return result;
}
