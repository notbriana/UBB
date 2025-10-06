#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include "service.h"

class GuiApartments : public QWidget {
    Q_OBJECT

private:
    Service& service;
    QListWidget* listWidget = new QListWidget();

    QPushButton* deleteButton = new QPushButton("Sterge");
    QPushButton* filterSurfaceButton = new QPushButton("Filtreaza suprafata");
    QPushButton* filterPriceButton = new QPushButton("Filtreaza pret");

    QLineEdit* minSurfaceLine = new QLineEdit();
    QLineEdit* maxSurfaceLine = new QLineEdit();
    QLineEdit* minPriceLine = new QLineEdit();
    QLineEdit* maxPriceLine = new QLineEdit();

public:
    GuiApartments(Service& s, QWidget* parent = nullptr);

private slots:
    void populate();
    void deleteApartment();
    void filterSurface();
    void filterPrice();
};
