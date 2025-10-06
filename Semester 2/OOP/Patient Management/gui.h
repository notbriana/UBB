#pragma once
#include <QWidget>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "service.h"

class DoctorWindow : public QWidget, public Observer {
    Q_OBJECT
    Service& service;
    Doctor doctor;
    QCheckBox* onlyMineBox;
    QListWidget* patientList;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QLineEdit* nameEdit, *diagEdit, *specEdit, *dateEdit;
    std::vector<Patient> currentPatients; // <-- Add this line

    void reload();
public:
    DoctorWindow(Service& s, const Doctor& d);
    void update() override;
};

class StatsWindow : public QWidget, public Observer {
    Q_OBJECT
    Service& service;
public:
    StatsWindow(Service& s);
    void update() override;
protected:
    void paintEvent(QPaintEvent* event) override;
};