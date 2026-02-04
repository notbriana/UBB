#include "star_model.h"

StarModel::StarModel(Service& s) : service(s) {
    refresh();
    service.addObserver([this]() { refresh(); });
}

int StarModel::rowCount(const QModelIndex&) const { return stars.size(); }
int StarModel::columnCount(const QModelIndex&) const { return 5; }

QVariant StarModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole) return {};
    const auto& s = stars[index.row()];
    switch (index.column()) {
        case 0: return QString::fromStdString(s.name);
        case 1: return QString::fromStdString(s.constellation);
        case 2: return s.ra;
        case 3: return s.dec;
        case 4: return s.diameter;
    }
    return {};
}

QVariant StarModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
        case 0: return "Name";
        case 1: return "Constellation";
        case 2: return "RA";
        case 3: return "Dec";
        case 4: return "Diameter";
    }
    return {};
}

void StarModel::setFilter(const std::string& constellation, bool active) {
    filterConstellation = constellation;
    filterActive = active;
    refresh();
}

void StarModel::refresh() {
    beginResetModel();
    if (filterActive)
        stars = service.getStarsByConstellation(filterConstellation);
    else
        stars = service.getStarsSorted();
    endResetModel();
}

const Star& StarModel::getStarAt(int row) const {
    return stars.at(row);
}