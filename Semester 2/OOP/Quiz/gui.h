#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class PresenterWindow : public QWidget {
    Q_OBJECT
    Service& service;
    QListWidget* list;
    QLineEdit *idEdit, *textEdit, *answerEdit, *scoreEdit;
    QPushButton* addBtn;
    QLabel* errorLabel;
    void refresh();
public:
    PresenterWindow(Service& s);
private slots:
    void onAdd();
};

class ParticipantWindow : public QWidget {
    Q_OBJECT
    Service& service;
    std::string participant;
    QListWidget* list;
    QLineEdit* answerEdit;
    QPushButton* answerBtn;
    QLabel* scoreLabel;
    void refresh();
public:
    ParticipantWindow(Service& s, const std::string& name);
private slots:
    void onAnswer();
    void onSelectionChanged();
};