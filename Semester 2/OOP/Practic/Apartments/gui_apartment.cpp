#include "gui_apartment.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

GuiApartments::GuiApartments(Service& s, QWidget* parent) : QWidget(parent), service(s) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(listWidget);
    layout->addWidget(deleteButton);
    layout->addWidget(new QLabel("Min suprafata"));
    layout->addWidget(minSurfaceLine);
    layout->addWidget(new QLabel("Max suprafata"));
    layout->addWidget(maxSurfaceLine);
    layout->addWidget(filterSurfaceButton);

    layout->addWidget(new QLabel("Min pret"));
    layout->addWidget(minPriceLine);
    layout->addWidget(new QLabel("Max pret"));
    layout->addWidget(maxPriceLine);
    layout->addWidget(filterPriceButton);

    setLayout(layout);
    populate();

    connect(deleteButton, &QPushButton::clicked, this, &GuiApartments::deleteApartment);
    connect(filterSurfaceButton, &QPushButton::clicked, this, &GuiApartments::filterSurface);
    connect(filterPriceButton, &QPushButton::clicked, this, &GuiApartments::filterPrice);
}

void GuiApartments::populate() {
    listWidget->clear();
    for (const auto& apt : service.getAll()) {
        listWidget->addItem(QString::fromStdString(apt.toString()));
    }
}

void GuiApartments::deleteApartment() {
    int row = listWidget->currentRow();
    if (row >= 0) {
        service.deleteApartment(row);
        populate();
    }
}

void GuiApartments::filterSurface() {
    int min = minSurfaceLine->text().toInt();
    int max = maxSurfaceLine->text().toInt();
    listWidget->clear();
    for (const auto& apt : service.filterBySurface(min, max)) {
        listWidget->addItem(QString::fromStdString(apt.toString()));
    }
}

void GuiApartments::filterPrice() {
    int minPrice = minPriceLine->text().toInt();
    int maxPrice = maxPriceLine->text().toInt();
    int minSurface = minSurfaceLine->text().isEmpty() ? -1 : minSurfaceLine->text().toInt();
    int maxSurface = maxSurfaceLine->text().isEmpty() ? -1 : maxSurfaceLine->text().toInt();

    listWidget->clear();
    for (const auto& apt : service.filterByPrice(minPrice, maxPrice, minSurface, maxSurface)) {
        listWidget->addItem(QString::fromStdString(apt.toString()));
    }
}
