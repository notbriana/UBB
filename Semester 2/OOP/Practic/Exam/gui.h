#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class DepartementWindow : public QWidget, public Observer {
    Service& service;
    Department dept;
    QListWidget* volunteerList;
    QListWidget* unassignedList;
    QLineEdit* nameEdit;
    QLineEdit* emailEdit;
    QLineEdit* interestsEdit;
    QPushButton* addButton;
    QPushButton* assignButton;
    QLabel* descriptionLabel;
    void updateLists();
public:
    DepartementWindow(Service& s, const Department& d);
    void update() override;
};

class StatisticWindow : public QWidget, public Observer {
    Service& service;
    QListWidget* statsList;
public:
    StatisticWindow(Service& s);
    void update() override;
};