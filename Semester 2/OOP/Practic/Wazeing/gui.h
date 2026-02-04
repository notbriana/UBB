#pragma once
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QSlider>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "service.h"
#include "domain.h"

class DriverWindow : public QWidget {
    Q_OBJECT
private:
    Driver driver;
    Service* service;
    QLabel* statusLabel;
    QLabel* locationLabel;
    QLabel* scoreLabel;
    QListWidget* reportsList;
    QSlider* radiusSlider;
    QLineEdit* descEdit;
    QLineEdit* latEdit;
    QLineEdit* lonEdit;
    int radius;

    void refresh();
    void moveDriver(int dLat, int dLon);

private slots:
    void onAddReport();
    void onValidateReport();
    void onRadiusChanged(int value);

public:
    DriverWindow(Driver driver, Service* service, QWidget* parent = nullptr);
};

class MapWindow : public QWidget {
    Q_OBJECT
private:
    Service* service;
protected:
    void paintEvent(QPaintEvent* event) override;
public:
    MapWindow(Service* service, QWidget* parent = nullptr);
};

void startGUI(Service& service, QApplication& app);
