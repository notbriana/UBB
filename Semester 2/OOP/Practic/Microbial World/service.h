#pragma once
#include "domain.h"
#include "filerepo.h"
#include <QObject>

class Service : public QObject {
    Q_OBJECT
    QVector<Biologist> biologists;
    QVector<Bacterium> bacteria;
    FileRepo& repo;
public:
    Service(FileRepo& r);

    const QVector<Biologist>& getBiologists() const;
    const QVector<Bacterium>& getBacteria() const;
    QVector<Bacterium> getBacteriaForSpecies(const QVector<QString>& species) const;
    QVector<QString> getSpeciesForBiologist(const QString& name) const;

    bool addBacterium(const Bacterium& b);
    bool updateBacterium(const QString& oldName, const QString& oldSpecies, const Bacterium& updated);
    void addDisease(const QString& bacteriumName, const QString& species, const QString& disease);

    void save();
signals:
    void dataChanged();
};