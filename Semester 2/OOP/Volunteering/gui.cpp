#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

DepartmentWindow::DepartmentWindow(Service& s, const Department& d) : service(s), dept(d) {
    setWindowTitle(QString::fromStdString(dept.getName()));
    QVBoxLayout* layout = new QVBoxLayout;
    descLabel = new QLabel(QString::fromStdString(dept.getDescription()));
    layout->addWidget(descLabel);

    volunteerList = new QListWidget;
    unassignedList = new QListWidget;
    layout->addWidget(new QLabel("Volunteers:"));
    layout->addWidget(volunteerList);
    layout->addWidget(new QLabel("Unassigned:"));
    layout->addWidget(unassignedList);

    nameEdit = new QLineEdit;
    emailEdit = new QLineEdit;
    interestsEdit = new QLineEdit;
    addBtn = new QPushButton("Add Volunteer");
    assignBtn = new QPushButton("Assign Selected");

    QHBoxLayout* form = new QHBoxLayout;
    form->addWidget(nameEdit);
    form->addWidget(emailEdit);
    form->addWidget(interestsEdit);
    form->addWidget(addBtn);
    layout->addLayout(form);
    layout->addWidget(assignBtn);

    setLayout(layout);

    connect(addBtn, &QPushButton::clicked, [this]() {
        try {
            QStringList interestsList = interestsEdit->text().split(',', Qt::SkipEmptyParts);
            std::vector<std::string> interestsVector;
            for (const QString& interest : interestsList) {
                interestsVector.push_back(interest.trimmed().toStdString());
            }
            service.addVolunteer(nameEdit->text().toStdString(), emailEdit->text().toStdString(), interestsVector);
            service.save();
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });

    connect(assignBtn, &QPushButton::clicked, [this]() {
        auto item = unassignedList->currentItem();
        if (item) service.assignVolunteer(item->text().toStdString(), dept.getName());
    });

    service.addObserver(this);
    update();
}

void DepartmentWindow::update() { updateLists(); }
void DepartmentWindow::updateLists() {
    volunteerList->clear();
    for (const auto& v : service.getVolunteersForDepartment(dept.getName()))
        volunteerList->addItem(QString::fromStdString(v.getName()));

    // Get all unassigned volunteers and their scores for this department
    std::vector<std::pair<Volunteer, double>> scoredUnassigned;
    auto unassigned = service.getUnassignedVolunteers();
    std::set<std::string> descWords;
    std::stringstream ss(dept.getDescription());
    std::string word;
    while (ss >> word) descWords.insert(word);

    for (const auto& v : unassigned) {
        int match = 0;
        for (const auto& interest : v.getInterests())
            if (descWords.count(interest)) ++match;
        double score = descWords.empty() ? 0.0 : (double)match / descWords.size();
        scoredUnassigned.push_back({v, score});
    }

    // Sort by score descending, then by name
    std::sort(scoredUnassigned.begin(), scoredUnassigned.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first.getName() < b.first.getName();
    });

    // Display all, highlight top 3
    unassignedList->clear();
    for (size_t i = 0; i < scoredUnassigned.size(); ++i) {
        const auto& v = scoredUnassigned[i].first;
        double score = scoredUnassigned[i].second;
        QString itemText = QString::fromStdString(v.getName()) + " (score: " + QString::number(score, 'f', 2) + ")";
        auto* item = new QListWidgetItem(itemText);
        if (i < 3) item->setBackground(Qt::yellow);
        unassignedList->addItem(item);
    }
}

StatsWindow::StatsWindow(Service& s) : service(s) {
    setWindowTitle("Department Stats");
    QVBoxLayout* layout = new QVBoxLayout;
    statsList = new QListWidget;
    layout->addWidget(statsList);
    setLayout(layout);
    service.addObserver(this);
    update();
}

void StatsWindow::update() {
    statsList->clear();
    std::vector<std::pair<std::string, int>> stats;
    for (const auto& d : service.getDepartments())
        stats.emplace_back(d.getName(), service.getVolunteersForDepartment(d.getName()).size());
    std::sort(stats.begin(), stats.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& s : stats)
        statsList->addItem(QString::fromStdString(s.first + ": " + std::to_string(s.second)));
}