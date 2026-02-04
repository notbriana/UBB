#pragma once
#include <QString>
#include <QVector>

class Bacterium {
public:
    QString name;
    QString species;
    int size;
    QVector<QString> diseases;

    Bacterium(const QString& n, const QString& s, int sz, const QVector<QString>& d)
        : name(n), species(s), size(sz), diseases(d) {}
};

class Biologist {
public:
    QString name;
    QVector<QString> studiedSpecies;

    Biologist(const QString& n, const QVector<QString>& s)
        : name(n), studiedSpecies(s) {}
};