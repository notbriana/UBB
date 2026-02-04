#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

UserWindow::UserWindow(const User& u, Service& s, QWidget* parent)
    : QWidget(parent), user(u), service(s) {
    setWindowTitle(QString::fromStdString(user.name + " (" + user.type + ")"));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    list = new QListWidget;
    mainLayout->addWidget(list);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    descEdit = new QLineEdit;
    addBtn = new QPushButton("Add");
    inputLayout->addWidget(new QLabel("Description:"));
    inputLayout->addWidget(descEdit);
    inputLayout->addWidget(addBtn);
    mainLayout->addLayout(inputLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    removeBtn = new QPushButton("Remove");
    resolveBtn = new QPushButton("Resolve");
    btnLayout->addWidget(removeBtn);
    btnLayout->addWidget(resolveBtn);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);

    connect(addBtn, &QPushButton::clicked, this, &UserWindow::onAdd);
    connect(removeBtn, &QPushButton::clicked, this, &UserWindow::onRemove);
    connect(resolveBtn, &QPushButton::clicked, this, &UserWindow::onResolve);
    connect(list, &QListWidget::itemSelectionChanged, this, &UserWindow::onSelectionChanged);

    service.addObserver([this]() { update(); });
    update();
}

void UserWindow::populate() {
    list->clear();
    auto issues = service.getSortedIssues();
    for (const auto& i : issues) {
        QString item = QString::fromStdString(i.description + " | " + i.status + " | " + i.reporter + " | " + i.solver);
        list->addItem(item);
    }
}

void UserWindow::onAdd() {
    try {
        if (user.type != "tester") throw std::runtime_error("Only testers can add issues.");
        service.addIssue(descEdit->text().toStdString(), user.name);
        descEdit->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::onRemove() {
    try {
        auto sel = list->currentRow();
        if (sel < 0) throw std::runtime_error("No issue selected.");
        auto issues = service.getSortedIssues();
        service.removeIssue(issues[sel].description);
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::onResolve() {
    try {
        if (user.type != "programmer") throw std::runtime_error("Only programmers can resolve issues.");
        auto sel = list->currentRow();
        if (sel < 0) throw std::runtime_error("No issue selected.");
        auto issues = service.getSortedIssues();
        if (issues[sel].status != "open") throw std::runtime_error("Issue is not open.");
        service.resolveIssue(issues[sel].description, user.name);
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::onSelectionChanged() {
    auto sel = list->currentRow();
    auto issues = service.getSortedIssues();
    bool canRemove = sel >= 0 && issues[sel].status == "closed";
    bool canResolve = sel >= 0 && issues[sel].status == "open" && user.type == "programmer";
    removeBtn->setEnabled(canRemove);
    resolveBtn->setEnabled(canResolve);
    addBtn->setEnabled(user.type == "tester");
}

void UserWindow::update() {
    populate();
    onSelectionChanged();
}