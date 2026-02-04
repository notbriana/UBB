#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "Service.h"
#include "Person.h"

class PersonWindow : public QWidget, public Observer {
    Q_OBJECT

    Service& service;
    Person person;

    QLabel* locationLabel;
    QListWidget* eventList;
    QCheckBox* nearCheck;
    QLabel* descriptionLabel;
    QTextEdit* descriptionEdit;
    QLineEdit* dateEdit;
    QPushButton* goingButton;
    QPushButton* addEventButton;
    QLineEdit* nameEdit;
    QLineEdit* latEdit;
    QLineEdit* lonEdit;
    QTextEdit* newDescEdit;
    QLineEdit* newDateEdit;
    QListWidget* attendeesList;
    QPushButton* updateEventButton;

    void setupUI();
    void connectSignals();

public:
    PersonWindow(Service& service, const Person& person, QWidget* parent = nullptr);
    void update() override;

private slots:
    void onEventSelectionChanged();
    void onNearCheckChanged(int state);
    void onGoingClicked();
    void onAddEventClicked();
    void onUpdateEventClicked();
};

class PopularEventsWindow : public QWidget, public Observer {
    Q_OBJECT

    Service& service;
    QListWidget* popularList;

    void setupUI();

public:
    PopularEventsWindow(Service& service, QWidget* parent = nullptr);
    void update() override;
};