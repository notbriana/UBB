#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "service.h"
#include "domain.h"

class ProgrammerWindow : public QWidget {
    Q_OBJECT
    Programmer programmer;
    Service& service;
    QListWidget* taskList;
    QLineEdit* descEdit;
    QPushButton* addBtn;
    QPushButton* removeBtn;
    QPushButton* startBtn;
    QPushButton* doneBtn;
    std::vector<int> indexMap;

    void refresh();
public:
    ProgrammerWindow(const Programmer& p, Service& s);
};