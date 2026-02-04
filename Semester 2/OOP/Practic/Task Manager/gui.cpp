#include "gui.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <algorithm>

ProgrammerWindow::ProgrammerWindow(const Programmer& p, Service& s)
    : programmer(p), service(s) {
    setWindowTitle(QString::fromStdString(programmer.name));
    QVBoxLayout* layout = new QVBoxLayout;
    taskList = new QListWidget;
    descEdit = new QLineEdit;
    addBtn = new QPushButton("Add");
    removeBtn = new QPushButton("Remove");
    startBtn = new QPushButton("Start");
    doneBtn = new QPushButton("Done");
    layout->addWidget(taskList);
    layout->addWidget(descEdit);
    layout->addWidget(addBtn);
    layout->addWidget(removeBtn);
    layout->addWidget(startBtn);
    layout->addWidget(doneBtn);
    setLayout(layout);

    refresh();
    service.addObserver([this]() { refresh(); });

    connect(addBtn, &QPushButton::clicked, [this]() {
        service.addTask(descEdit->text().toStdString());
        descEdit->clear();
    });
    connect(removeBtn, &QPushButton::clicked, [this]() {
        int idx = taskList->currentRow();
        if (idx >= 0 && idx < static_cast<int>(indexMap.size()))
            service.removeTask(indexMap[idx]);
    });
    connect(startBtn, &QPushButton::clicked, [this]() {
        int idx = taskList->currentRow();
        if (idx >= 0 && idx < static_cast<int>(indexMap.size())) {
            try { service.startTask(indexMap[idx], programmer.id); }
            catch (std::exception& e) { QMessageBox::warning(this, "Error", e.what()); }
        }
    });
    connect(doneBtn, &QPushButton::clicked, [this]() {
        int idx = taskList->currentRow();
        if (idx >= 0 && idx < static_cast<int>(indexMap.size())) {
            try { service.closeTask(indexMap[idx], programmer.id); }
            catch (std::exception& e) { QMessageBox::warning(this, "Error", e.what()); }
        }
    });
}

void ProgrammerWindow::refresh() {
    taskList->clear();
    indexMap.clear();
    auto& tasks = service.getTasks();
    std::vector<std::pair<int, Task>> indexedTasks;
    for (size_t i = 0; i < tasks.size(); ++i)
        indexedTasks.emplace_back(static_cast<int>(i), tasks[i]);
    std::sort(indexedTasks.begin(), indexedTasks.end(), [](const auto& a, const auto& b) {
        return (int)a.second.status < (int)b.second.status;
    });
    for (const auto& pair : indexedTasks) {
        const Task& t = pair.second;
        QString item = QString::fromStdString(t.description) + " | ";
        if (t.status == TaskStatus::Open) item += "open";
        else if (t.status == TaskStatus::InProgress) item += "in progress";
        else item += "closed";
        if (t.status != TaskStatus::Open)
            item += QString(" | Programmer ID: %1").arg(t.programmerId);
        taskList->addItem(item);
        indexMap.push_back(pair.first); // map displayed index to real index
    }
}