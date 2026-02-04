#pragma once

#include <QtWidgets/QMainWindow>
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSplitter>

class GuiCar : public QMainWindow
{
    Q_OBJECT

public:
    GuiCar(QWidget* parent = nullptr);
    ~GuiCar();

private:
    Service service;

    // UI Elements
    QListWidget* allCarsListWidget;
    QLabel* allCarsLabel;
    QLabel* manufacturerInputLabel;
    QLineEdit* manufacturerInput;
    QPushButton* showCarsButton;
    QListWidget* manufacturerCarsListWidget;
    QLabel* manufacturerCarsLabel;
    QLabel* carCountLabel;
    QLineEdit* carCountDisplay;

    void loadAllCars();
    void updateCarsList(QListWidget* listWidget, const std::vector<Car>& carsToShow);

public slots:
    void showCarsByManufacturer();
};
