#pragma once
#include "domain.h"
#include <QVector>
#include <QString>

class FileRepo {
    QString biologistsFile, bacteriaFile;
public:
    FileRepo(const QString& bioF, const QString& bacF)
        : biologistsFile(bioF), bacteriaFile(bacF) {}

    QVector<Biologist> loadBiologists();
    QVector<Bacterium> loadBacteria();
    void saveBacteria(const QVector<Bacterium>& bacteria);
};