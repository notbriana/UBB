#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

IdeasModel::IdeasModel(Service& s, const std::string& r, QObject* parent)
    : QAbstractTableModel(parent), service(s), researcher(r) {}

int IdeasModel::rowCount(const QModelIndex&) const { return service.getIdeasSorted().size(); }
int IdeasModel::columnCount(const QModelIndex&) const { return 4; }
QVariant IdeasModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole) return {};
    const auto& ideas = service.getIdeasSorted();
    if (index.row() >= ideas.size()) return {};
    const auto& idea = ideas[index.row()];
    switch (index.column()) {
        case 0: return QString::fromStdString(idea.title);
        case 1: return QString::fromStdString(idea.status);
        case 2: return QString::fromStdString(idea.creator);
        case 3: return idea.duration;
    }
    return {};
}
void IdeasModel::refresh() {
    beginResetModel();
    endResetModel();
}

ResearcherWindow::ResearcherWindow(Service& s, const Researcher& r, QWidget* parent)
    : QWidget(parent), service(s), researcher(r) {
    model = new IdeasModel(service, researcher.name, this);
    setupUI();
    connectSignals();
    setWindowTitle(QString::fromStdString(researcher.name));
    service.addObserver([this]() { model->refresh(); updateButtons(); });
    updateButtons();
}

void ResearcherWindow::setupUI() {
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString::fromStdString("Position: " + researcher.position)));
    table = new QTableView;
    table->setModel(model);
    layout->addWidget(table);

    auto* form = new QHBoxLayout;
    titleEdit = new QLineEdit; descEdit = new QLineEdit; durationEdit = new QLineEdit;
    form->addWidget(new QLabel("Title:")); form->addWidget(titleEdit);
    form->addWidget(new QLabel("Desc:")); form->addWidget(descEdit);
    form->addWidget(new QLabel("Duration:")); form->addWidget(durationEdit);
    addBtn = new QPushButton("Add Idea");
    form->addWidget(addBtn);
    layout->addLayout(form);

    acceptBtn = new QPushButton("Accept Idea");
    developBtn = new QPushButton("Develop");
    saveAllBtn = new QPushButton("Save all");
    layout->addWidget(acceptBtn);
    layout->addWidget(developBtn);
    if (researcher.position == "senior") layout->addWidget(saveAllBtn);
}

void ResearcherWindow::connectSignals() {
    connect(addBtn, &QPushButton::clicked, [this]() {
        try {
            service.addIdea(titleEdit->text().toStdString(), descEdit->text().toStdString(),
                            researcher.name, durationEdit->text().toInt());
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });
    connect(acceptBtn, &QPushButton::clicked, [this]() {
        auto idx = table->currentIndex();
        if (!idx.isValid()) return;
        auto title = model->data(model->index(idx.row(), 0)).toString().toStdString();
        try {
            service.acceptIdea(title, researcher.name); // Pass researcher's name
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });
    connect(developBtn, &QPushButton::clicked, [this]() {
        auto ideas = service.getIdeasSorted();
        for (const auto& idea : ideas) {
            if (idea.creator == researcher.name && idea.status == "accepted") {
                QWidget* w = new QWidget;
                auto* l = new QVBoxLayout(w);
                auto* descEdit = new QLineEdit(QString::fromStdString(idea.description));
                auto* saveBtn = new QPushButton("Save");
                l->addWidget(new QLabel(QString::fromStdString(idea.title)));
                l->addWidget(descEdit);
                l->addWidget(saveBtn);
                connect(saveBtn, &QPushButton::clicked, [this, descEdit, idea, w]() {
                    service.updateIdeaDescription(idea.title, descEdit->text().toStdString());
                    service.saveIdeaToFile(idea);
                    w->close();
                });
                w->show();
            }
        }
    });
    if (saveAllBtn)
        connect(saveAllBtn, &QPushButton::clicked, [this]() {
            service.saveAllAcceptedIdeas("all_accepted_ideas.txt");
        });
}

void ResearcherWindow::updateButtons() {
    bool hasAccepted = false;
    for (const auto& idea : service.getIdeasSorted())
        if (idea.creator == researcher.name && idea.status == "accepted")
            hasAccepted = true;
    developBtn->setEnabled(hasAccepted);
    acceptBtn->setEnabled(researcher.position == "senior");
}