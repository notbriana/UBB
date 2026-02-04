#pragma once
#include <QWidget>
#include "service.h"
#include "star_model.h"
#include <QTableView>
#include <QMessageBox>
#include <QListWidget>

class AstronomerWindow : public QWidget {
    Q_OBJECT
    Service& service;
    Astronomer astronomer;
    StarModel* model;

    QTableView* table;
    QCheckBox* filterBox;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QPushButton* viewBtn;
    QLineEdit* searchEdit;
    QListWidget* searchList;

    void setupUI();
    void connectSignals();

public:
    AstronomerWindow(Service& s, const Astronomer& a, QWidget* parent = nullptr);
};