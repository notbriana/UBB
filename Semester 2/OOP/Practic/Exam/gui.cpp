#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

DepartementWindow::DepartementWindow(Service& s, const Department& d) : service(s), dept(d) {
    setWindowTitle(QString::fromStdString(dept.getName()));
    QVBoxLayout* layout = new QVBoxLayout;
    descriptionLabel = new QLabel(QString::fromStdString(dept.getDescription()));
    layout->addWidget(descriptionLabel);

    volunteerList = new QListWidget;
    unassignedList = new QListWidget;
    layout->addWidget(new QLabel("Volunteers for this departement:"));
    layout->addWidget(volunteerList);
    layout->addWidget(new QLabel("Unassigned volunteers:"));
    layout->addWidget(unassignedList);

    nameEdit = new QLineEdit;
    emailEdit = new QLineEdit;
    interestsEdit = new QLineEdit;
    addButton = new QPushButton("Add Volunteer");
    assignButton = new QPushButton("Assign Selected");

    QHBoxLayout* form = new QHBoxLayout;
    form->addWidget(nameEdit);
    form->addWidget(emailEdit);
    form->addWidget(interestsEdit);
    form->addWidget(addButton);
    layout->addLayout(form);
    layout->addWidget(assignButton);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, [this]() {
        try {
            QStringList interestsList = interestsEdit->text().split(',', Qt::SkipEmptyParts);
            std::vector<std::string> interestsVector;
            for (const QString& interest : interestsList) {
                interestsVector.push_back(interest.trimmed().toStdString());
            }
            service.addVolunteer(nameEdit->text().toStdString(), emailEdit->text().toStdString(), interestsVector);
            service.save();
        }
        catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(assignButton, &QPushButton::clicked, [this]() {
        auto item = unassignedList->currentItem();
        QString text = item->text();
        QString name = text.section(" (score:", 0, 0);
        service.assignVolunteer(name.toStdString(), dept.getName());
        service.save();
        updateLists();
        });

    service.addObserver(this);
    update();
}

void DepartementWindow::update() 
{ 
    updateLists(); 
}

void DepartementWindow::updateLists() {
    volunteerList->clear();
    for (const auto& v : service.getVolunteersPerDepartment(dept.getName()))
    {
        volunteerList->addItem(QString::fromStdString(v.getName()));
        volunteerList->addItem(QString::fromStdString(v.getEmail()));
        volunteerList->addItem(QString::fromStdString(v.getDepartment()));
    }
    std::vector<std::pair<Volunteer, double>> scoreUnasigned;
    auto unassigned = service.getVolunteersUnassigned();
    std::set<std::string> descrptionWords;
    std::stringstream ss(dept.getDescription());
    std::string word;
    while (ss >> word) descrptionWords.insert(word);

    for (const auto& v : unassigned) {
        int match = 0;
        for (const auto& interest : v.getInterests())
            if (descrptionWords.count(interest)) ++match;
        double score = descrptionWords.empty() ? 0.0 : (double)match / descrptionWords.size();
        scoreUnasigned.push_back({ v, score });
    }

    std::sort(scoreUnasigned.begin(), scoreUnasigned.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first.getName() < b.first.getName();
        });

    unassignedList->clear();
    for (size_t i = 0; i < scoreUnasigned.size(); ++i) {
        const auto& v = scoreUnasigned[i].first;
        double score = scoreUnasigned[i].second;
        QString itemText = QString::fromStdString(v.getName()) + " (score: " + QString::number(score, 'f', 2) + ")";
        auto* item = new QListWidgetItem(itemText);
        if (i < 3) item->setBackground(Qt::yellow);
        unassignedList->addItem(item);
    }
}

StatisticWindow::StatisticWindow(Service& s) : service(s) {
    setWindowTitle("Department Stats");
    QVBoxLayout* layout = new QVBoxLayout;
    statsList = new QListWidget;
    layout->addWidget(statsList);
    setLayout(layout);
    service.addObserver(this);
    update();
}

void StatisticWindow::update() {
    statsList->clear();
    std::vector<std::pair<std::string, int>> stats;
    for (const auto& d : service.getDepartments())
        stats.emplace_back(d.getName(), service.getVolunteersPerDepartment(d.getName()).size());
    std::sort(stats.begin(), stats.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& s : stats)
        statsList->addItem(QString::fromStdString(s.first + ": " + std::to_string(s.second)));
}