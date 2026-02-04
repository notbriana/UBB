#include "gui_documents.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    gui_documents window;
    window.show();
    return app.exec();
}
