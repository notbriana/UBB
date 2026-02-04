#include "gui.h"
#include "statisticswindow.h"
#include <QMessageBox>



ProgrammerWindow::ProgrammerWindow(CodeRevisionService& service, Programmer programmer)
    : service(service), programmer(programmer) {

    this->setWindowTitle(QString::fromStdString(programmer.name));
    auto* layout = new QVBoxLayout;

    label = new QLabel;
    layout->addWidget(label);

    list = new QListWidget;
    layout->addWidget(list);

    reviseButton = new QPushButton("Revise");
    layout->addWidget(reviseButton);

    setLayout(layout);
    updateView();

    QObject::connect(reviseButton, &QPushButton::clicked, this, &ProgrammerWindow::handleRevise);
    service.addObserver([this]() { updateView(); });
    fileInput = new QLineEdit;
    layout->addWidget(fileInput);

    addButton = new QPushButton("Add");
    layout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, this, &ProgrammerWindow::handleAddFile);

    statsButton = new QPushButton("Show Statistics");
    layout->addWidget(statsButton);
    connect(statsButton, &QPushButton::clicked, this, &ProgrammerWindow::showStatistics);
}

void ProgrammerWindow::handleAddFile() {
    std::string filename = fileInput->text().toStdString();
    std::string error;
    if (!service.addFile(filename, programmer.name, error)) {
        QMessageBox::warning(this, "Add File Error", QString::fromStdString(error));
    }
    fileInput->clear();
}


void ProgrammerWindow::updateView() {
    list->clear();
    int count = 0;

    for (const auto& file : service.getFilesSorted()) {
        QString display = QString::fromStdString(file.name + " | " + file.status + " | " + file.creator + " | " + file.reviewer);
        QListWidgetItem* item = new QListWidgetItem(display);

        if (file.status == "not_revised") {
            QFont font;
            font.setBold(true);
            item->setFont(font);
        }
        else if (file.reviewer == programmer.name) {
            item->setBackground(Qt::green);
        }

        list->addItem(item);
        if (file.reviewer == programmer.name) count++;
    }

    programmer.revised_files = count; // <-- Update the programmer's revised_files count

    label->setText(QString("%1/%2 files revised").arg(count).arg(programmer.total_files_to_revise));
    if (count == programmer.total_files_to_revise) {
        QMessageBox::information(this, "Congratulations", "You revised all your files!");
    }
}

void ProgrammerWindow::handleRevise() {
    auto* item = list->currentItem();
    if (!item) return;

    std::string name = item->text().split("|")[0].trimmed().toStdString();
    service.reviseFile(name, programmer.name);
}


void ProgrammerWindow::showStatistics() {
    std::vector<Programmer> allProgrammers = service.getAllProgrammers(); // Ensure this method is implemented in the service
    StatisticsWindow* statsWin = new StatisticsWindow(allProgrammers, this); // Explicitly specify the type
    statsWin->show();
}