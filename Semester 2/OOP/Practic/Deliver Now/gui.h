#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include "mapwidget.h"
#include "service.h"
#include "observer.h"

class GUI : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;

    // Company window widgets

    QListWidget* courierList;
    QPushButton* showMapButton;
    QListWidget* allPackagesList;
    // Map window
    QWidget* mapWidget;

    // Delivery windows per courier
    std::vector<QDialog*> courierWindows;

    void setupCompanyWindow();
    void openMapWindow();

public:
    GUI(Service& service);
    void start();
    void refreshAllPackagesList();
    void update() override; // Observer method    
    void openCourierWindow(const Courier& c);

};
