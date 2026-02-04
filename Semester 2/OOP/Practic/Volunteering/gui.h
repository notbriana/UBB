#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class DepartmentWindow : public QWidget, public Observer {
    Service& service;
    Department dept;
    QListWidget* volunteerList;
    QListWidget* unassignedList;
    QLineEdit* nameEdit;
    QLineEdit* emailEdit;
    QLineEdit* interestsEdit;
    QPushButton* addBtn;
    QPushButton* assignBtn;
    QLabel* descLabel;
    void updateLists();
public:
    DepartmentWindow(Service& s, const Department& d);
    void update() override;
};

class StatsWindow : public QWidget, public Observer {
    Service& service;
    QListWidget* statsList;
public:
    StatsWindow(Service& s);
    void update() override;
};