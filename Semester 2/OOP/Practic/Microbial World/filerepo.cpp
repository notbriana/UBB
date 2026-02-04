#include "filerepo.h"
#include <QFile>
#include <QTextStream>

QVector<Biologist> FileRepo::loadBiologists() {
    QVector<Biologist> result;
    QFile file(biologistsFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return result;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(';');
        if (parts.size() < 2) continue;
        QString name = parts[0];
        QVector<QString> species = parts[1].split(',').toVector();
        result.append(Biologist(name, species));
    }
    return result;
}

QVector<Bacterium> FileRepo::loadBacteria() {
    QVector<Bacterium> result;
    QFile file(bacteriaFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return result;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(';');
        if (parts.size() < 4) continue;
        QString name = parts[0];
        QString species = parts[1];
        int size = parts[2].toInt();
        QVector<QString> diseases = parts[3].split(',').toVector();
        result.append(Bacterium(name, species, size, diseases));
    }
    return result;
}

void FileRepo::saveBacteria(const QVector<Bacterium>& bacteria) {
    QFile file(bacteriaFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for (const auto& b : bacteria) {
        out << b.name << ";" << b.species << ";" << b.size << ";"
            << b.diseases.join(",") << "\n";
    }
}