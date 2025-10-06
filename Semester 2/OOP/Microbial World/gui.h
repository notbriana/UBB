#pragma once
#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include "service.h"
#include <QAbstractTableModel>

class BacteriaTableModel : public QAbstractTableModel {
    Q_OBJECT
    QVector<Bacterium> bacteria;
    Service* service; // Add this
public:
    BacteriaTableModel(Service* s, QObject* parent = nullptr) : QAbstractTableModel(parent), service(s) {}
    void setBacteria(const QVector<Bacterium>& b);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    Bacterium getBacterium(int row) const;
signals:
    void bacteriumEdited(int row, const Bacterium& b);
};

class BiologistWindow : public QWidget {
    Q_OBJECT
    Service& service;
    Biologist biologist;
    BacteriaTableModel* model;
    QTableView* table;
    QComboBox* speciesCombo;
    QListWidget* diseaseList;
    QPushButton* addBacteriumBtn;
    QPushButton* addDiseaseBtn;
    QPushButton* viewBtn;

    void refreshTable();
    void refreshSpeciesCombo();
    void refreshDiseaseList(int row);
public:
    BiologistWindow(Service& s, const Biologist& b, QWidget* parent = nullptr);
};