#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "service.h"
#include <QAbstractTableModel>

class IdeasModel : public QAbstractTableModel {
    Q_OBJECT
    Service& service;
    std::string researcher;
public:
    IdeasModel(Service& s, const std::string& r, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void refresh();
};

class ResearcherWindow : public QWidget {
    Q_OBJECT
    Service& service;
    Researcher researcher;
    IdeasModel* model;
    QTableView* table;
    QLineEdit *titleEdit, *descEdit, *durationEdit;
    QPushButton *addBtn, *acceptBtn, *developBtn, *saveAllBtn;
    void setupUI();
    void connectSignals();
    void updateButtons();
public:
    ResearcherWindow(Service& s, const Researcher& r, QWidget* parent = nullptr);
};