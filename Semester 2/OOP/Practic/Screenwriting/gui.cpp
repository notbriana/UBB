#include "gui.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFileDialog>

WriterWindow::WriterWindow(Service& s, const Writer& w, QWidget* parent)
    : QWidget(parent), service(s), writer(w) {
    setupUI();
    loadIdeas();
    connectSignals();
    setWindowTitle(QString::fromStdString(writer.getName()));
}

void WriterWindow::setupUI() {
    auto* layout = new QVBoxLayout(this);
    model = new QStandardItemModel(0, 4, this);
    model->setHorizontalHeaderLabels({"Description", "Status", "Creator", "Act"});
    table = new QTableView(this);
    table->setModel(model);
    layout->addWidget(table);

    auto* formLayout = new QHBoxLayout();
    descEdit = new QLineEdit(this);
    actEdit = new QLineEdit(this);
    addBtn = new QPushButton("Add Idea", this);
    formLayout->addWidget(descEdit);
    formLayout->addWidget(actEdit);
    formLayout->addWidget(addBtn);
    layout->addLayout(formLayout);

    acceptBtn = new QPushButton("Accept Idea", this);
    if (writer.getExpertise() == "Senior")
        layout->addWidget(acceptBtn);

    developBtn = new QPushButton("Develop", this);
    layout->addWidget(developBtn);

    savePlotBtn = new QPushButton("Save plot", this);
    layout->addWidget(savePlotBtn);

    setLayout(layout);
}

void WriterWindow::loadIdeas() {
    model->setRowCount(0);
    auto ideas = service.getIdeasSorted();
    for (const auto& idea : ideas) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(idea.getDescription()))
            << new QStandardItem(QString::fromStdString(idea.getStatus()))
            << new QStandardItem(QString::fromStdString(idea.getCreator()))
            << new QStandardItem(QString::number(idea.getAct()));
        model->appendRow(row);
    }
}

void WriterWindow::connectSignals() {
    connect(addBtn, &QPushButton::clicked, [this]() {
        try {
            service.addIdea(descEdit->text().toStdString(), writer.getName(), actEdit->text().toInt());
            loadIdeas();
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });
    if (writer.getExpertise() == "Senior") {
        connect(acceptBtn, &QPushButton::clicked, [this]() {
            auto idx = table->currentIndex();
            if (!idx.isValid()) return;
            auto desc = model->item(idx.row(), 0)->text().toStdString();
            int act = model->item(idx.row(), 3)->text().toInt();
            try {
                service.acceptIdea(desc, act, writer.getName());
                loadIdeas();
            } catch (std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        });
    }
    connect(developBtn, &QPushButton::clicked, [this]() { showDevelopWindows(); });
    connect(savePlotBtn, &QPushButton::clicked, [this]() {
        QString file = QFileDialog::getSaveFileName(this, "Save Plot");
        if (!file.isEmpty()) service.savePlot(file.toStdString());
    });
}

void WriterWindow::showDevelopWindows() {
    auto ideas = service.getIdeasSorted();
    for (const auto& idea : ideas) {
        if (idea.getCreator() == writer.getName() && idea.getStatus() == "accepted") {
            auto* devWin = new QWidget;
            auto* layout = new QVBoxLayout(devWin);
            auto* edit = new QTextEdit(devWin);
            auto* saveBtn = new QPushButton("Save", devWin);
            layout->addWidget(edit);
            layout->addWidget(saveBtn);
            devWin->setLayout(layout);
            devWin->setWindowTitle(QString::fromStdString(idea.getDescription()));
            connect(saveBtn, &QPushButton::clicked, [this, edit, idea, devWin]() {
                try {
                    service.developIdea(idea.getDescription(), idea.getAct(), edit->toPlainText().toStdString(), writer.getName());
                    devWin->close();
                } catch (std::exception& e) {
                    QMessageBox::warning(devWin, "Error", e.what());
                }
            });
            devWin->show();
        }
    }
}