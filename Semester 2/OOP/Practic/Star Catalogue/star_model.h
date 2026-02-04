#pragma once
#include <QAbstractTableModel>
#include "service.h"

class StarModel : public QAbstractTableModel {
    Q_OBJECT
    Service& service;
    std::vector<Star> stars;
    std::string filterConstellation;
    bool filterActive = false;
public:
    StarModel(Service& s);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setFilter(const std::string& constellation, bool active);
    void refresh();
    const Star& getStarAt(int row) const;
};