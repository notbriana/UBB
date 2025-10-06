#include "gui.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cmath>
#include <set>

// Constructor
GUI::GUI(Service& service) : service(service) {
    setupCompanyWindow();
}

// Company Window (Main Window)
void GUI::setupCompanyWindow() {
    this->setWindowTitle("Package Company");
    QVBoxLayout* layout = new QVBoxLayout;

    courierList = new QListWidget;
    for (auto& c : service.getCouriers()) {
        courierList->addItem(QString::fromStdString(c.getName()));
    }

    QPushButton* openCourierBtn = new QPushButton("Open Courier Window");
    connect(openCourierBtn, &QPushButton::clicked, [=]() {
        int idx = courierList->currentRow();
        if (idx >= 0 && idx < service.getCouriers().size()) {
            openCourierWindow(service.getCouriers()[idx]);
        }
    });

    showMapButton = new QPushButton("Show Map");
    connect(showMapButton, &QPushButton::clicked, [=]() {
        openMapWindow();
    });

    // Combo box for streets
    QComboBox* streetCombo = new QComboBox;
    streetCombo->addItem("All Streets");
    // Collect all unique streets from all couriers
    std::set<std::string> allStreets;
    for (const auto& c : service.getCouriers()) {
        for (const auto& s : c.getStreets()) {
            allStreets.insert(s);
        }
    }
    for (const auto& s : allStreets) {
        streetCombo->addItem(QString::fromStdString(s));
    }

    QListWidget* pkgList = new QListWidget;

    // Function to refresh package list based on selected street
    auto refreshList = [this, pkgList, streetCombo]() {
        pkgList->clear();
        std::string selectedStreet = streetCombo->currentIndex() == 0 ? "" : streetCombo->currentText().toStdString();
        for (const auto& pkg : service.getAllPackages()) {
            std::string pkgStreet = pkg.getStreet();
            if (selectedStreet.empty() || pkgStreet == selectedStreet) {
                auto* item = new QListWidgetItem(
                    QString::fromStdString(pkg.getRecipient() + " - " + pkg.getAddress()));
                if (pkg.isDelivered())
                    item->setBackground(Qt::green);
                pkgList->addItem(item);
            }
        }
    };

    refreshList();
    connect(streetCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), refreshList);

    layout->addWidget(new QLabel("Select a Courier:"));
    layout->addWidget(courierList);
    layout->addWidget(openCourierBtn);
    layout->addWidget(showMapButton);
    layout->addWidget(new QLabel("Filter packages by street:"));
    layout->addWidget(streetCombo);
    layout->addWidget(pkgList);

    this->setLayout(layout);
    this->resize(350, 400);
}

// Courier Window
void GUI::openCourierWindow(const Courier& courier) {
    QDialog* window = new QDialog;
    window->setWindowTitle(QString::fromStdString("Courier: " + courier.getName()));
    QVBoxLayout* layout = new QVBoxLayout;

    QListWidget* pkgList = new QListWidget;
    auto pkgs = service.getPackagesForCourier(courier);
    for (auto& p : pkgs) {
        pkgList->addItem(QString::fromStdString(p.getRecipient() + " - " + p.getAddress()));
    }

    QPushButton* deliverBtn = new QPushButton("Deliver Selected Package");
    connect(deliverBtn, &QPushButton::clicked, [=]() {
        int idx = pkgList->currentRow();
        if (idx >= 0 && idx < pkgs.size()) {
            service.deliverPackage(pkgs[idx]);
            pkgList->takeItem(idx);
        }
    });

    layout->addWidget(new QLabel("Packages for " + QString::fromStdString(courier.getName())));
    layout->addWidget(pkgList);
    layout->addWidget(deliverBtn);

    window->setLayout(layout);
    window->resize(400, 300);
    window->show();

    courierWindows.push_back(window);
}

// Map Window
void GUI::openMapWindow() {
    if (mapWidget) {
        mapWidget->close();
        delete mapWidget;
    }

    mapWidget = new MapWidget(service);
    mapWidget->setWindowTitle("Map View");
    mapWidget->resize(600, 600);
    mapWidget->show();
}

void GUI::refreshAllPackagesList() {
    // Find the street combo and package list widgets
    QComboBox* streetCombo = nullptr;
    QListWidget* pkgList = nullptr;
    // Find children by type (assumes only one of each in the main window)
    for (auto* child : this->findChildren<QComboBox*>()) streetCombo = child;
    for (auto* child : this->findChildren<QListWidget*>()) {
        // Skip courierList
        if (child != courierList) pkgList = child;
    }
    if (!pkgList) return;

    pkgList->clear();
    std::string selectedStreet;
    if (streetCombo && streetCombo->currentIndex() > 0)
        selectedStreet = streetCombo->currentText().toStdString();

    for (const auto& pkg : service.getAllPackages()) {
        if (selectedStreet.empty() || pkg.getStreet() == selectedStreet) {
            auto* item = new QListWidgetItem(
                QString::fromStdString(pkg.getRecipient() + " - " + pkg.getAddress()));
            if (pkg.isDelivered())
                item->setBackground(Qt::green);
            pkgList->addItem(item);
        }
    }
}

void GUI::update() {
    // Refresh the package list in the company window
    refreshAllPackagesList();
    // Optionally, refresh courier windows and map window if needed
    for (auto* win : courierWindows) {
        if (win && win->isVisible()) {
            win->close();
        }
    }
    courierWindows.clear();
    for (const auto& c : service.getCouriers()) {
        openCourierWindow(c);
    }
    if (mapWidget) {
        mapWidget->update();
    }
}

// Entry point to show main window
void GUI::start() {
    this->show();
}
