#include "service.h"

Service::Service(FileRepo& r) : repo(r) {
    biologists = repo.loadBiologists();
    bacteria = repo.loadBacteria();
}

const QVector<Biologist>& Service::getBiologists() const { return biologists; }
const QVector<Bacterium>& Service::getBacteria() const { return bacteria; }

QVector<Bacterium> Service::getBacteriaForSpecies(const QVector<QString>& species) const {
    QVector<Bacterium> result;
    for (const auto& b : bacteria)
        if (species.contains(b.species))
            result.append(b);
    std::sort(result.begin(), result.end(), [](const Bacterium& a, const Bacterium& b) {
        return a.name < b.name;
    });
    return result;
}

QVector<QString> Service::getSpeciesForBiologist(const QString& name) const {
    for (const auto& bio : biologists)
        if (bio.name == name)
            return bio.studiedSpecies;
    return {};
}

bool Service::addBacterium(const Bacterium& b) {
    for (const auto& existing : bacteria)
        if (existing.name == b.name && existing.species == b.species)
            return false;
    bacteria.append(b);
    emit dataChanged();
    save();
    return true;
}

bool Service::updateBacterium(const QString& oldName, const QString& oldSpecies, const Bacterium& updated) {
    for (auto& b : bacteria) {
        if (b.name == oldName && b.species == oldSpecies) {
            b = updated;
            emit dataChanged();
            save();
            return true;
        }
    }
    return false;
}

void Service::addDisease(const QString& bacteriumName, const QString& species, const QString& disease) {
    for (auto& b : bacteria) {
        if (b.name == bacteriumName && b.species == species) {
            if (!b.diseases.contains(disease))
                b.diseases.append(disease);
            emit dataChanged();
            return;
        }
    }
    
}

void Service::save() { repo.saveBacteria(bacteria); }