#include "gui.h"
#include "service.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QTimer>
#include <QMap>
#include <QGroupBox>
#include <QPainter>

// Helper for distance calculation
static double distance(double lat1, double lon1, double lat2, double lon2) {
    return sqrt((lat1 - lat2) * (lat1 - lat2) + (lon1 - lon2) * (lon1 - lon2));
}

// --- DriverWindow Implementation ---

DriverWindow::DriverWindow(Driver driver, Service* service, QWidget* parent)
    : QWidget(parent), driver(driver), service(service), radius(10)
{
    setWindowTitle(QString::fromStdString(driver.getName()));
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Status, location, score
    statusLabel = new QLabel(this);
    locationLabel = new QLabel(this);
    scoreLabel = new QLabel(this);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(locationLabel);
    mainLayout->addWidget(scoreLabel);

    // Reports list
    reportsList = new QListWidget(this);
    mainLayout->addWidget(reportsList);

    // Add report
    QGroupBox* addReportBox = new QGroupBox("Add Report", this);
    QHBoxLayout* addReportLayout = new QHBoxLayout(addReportBox);
    descEdit = new QLineEdit(this);
    latEdit = new QLineEdit(this);
    lonEdit = new QLineEdit(this);
    QPushButton* addReportBtn = new QPushButton("Add", this);
    addReportLayout->addWidget(new QLabel("Desc:"));
    addReportLayout->addWidget(descEdit);
    addReportLayout->addWidget(new QLabel("Lat:"));
    addReportLayout->addWidget(latEdit);
    addReportLayout->addWidget(new QLabel("Lon:"));
    addReportLayout->addWidget(lonEdit);
    addReportLayout->addWidget(addReportBtn);
    mainLayout->addWidget(addReportBox);

    // Validate report
    QPushButton* validateBtn = new QPushButton("Validate Selected", this);
    mainLayout->addWidget(validateBtn);

    // Radius slider
    QHBoxLayout* sliderLayout = new QHBoxLayout();
    QLabel* sliderLabel = new QLabel("Search radius:", this);
    radiusSlider = new QSlider(Qt::Horizontal, this);
    radiusSlider->setRange(1, 50);
    radiusSlider->setValue(10);
    sliderLayout->addWidget(sliderLabel);
    sliderLayout->addWidget(radiusSlider);
    mainLayout->addLayout(sliderLayout);

    // Location update buttons
    QHBoxLayout* moveLayout = new QHBoxLayout();
    QPushButton* northBtn = new QPushButton("North", this);
    QPushButton* southBtn = new QPushButton("South", this);
    QPushButton* eastBtn = new QPushButton("East", this);
    QPushButton* westBtn = new QPushButton("West", this);
    moveLayout->addWidget(northBtn);
    moveLayout->addWidget(southBtn);
    moveLayout->addWidget(eastBtn);
    moveLayout->addWidget(westBtn);
    mainLayout->addLayout(moveLayout);

    // Connect signals
    connect(addReportBtn, &QPushButton::clicked, this, &DriverWindow::onAddReport);
    connect(validateBtn, &QPushButton::clicked, this, &DriverWindow::onValidateReport);
    connect(radiusSlider, &QSlider::valueChanged, this, &DriverWindow::onRadiusChanged);
    connect(northBtn, &QPushButton::clicked, this, [this]() { moveDriver(1, 0); });
    connect(southBtn, &QPushButton::clicked, this, [this]() { moveDriver(-1, 0); });
    connect(eastBtn, &QPushButton::clicked, this, [this]() { moveDriver(0, 1); });
    connect(westBtn, &QPushButton::clicked, this, [this]() { moveDriver(0, -1); });

    // Listen for updates
    connect(service, &Service::dataChanged, this, &DriverWindow::refresh);

    refresh();
}

void DriverWindow::refresh() {
    // Update driver info
    driver = service->getDriver(driver.getName());
    statusLabel->setText("Status: " + QString::fromStdString(driver.getStatus()));
    locationLabel->setText("Location: (" + QString::number(driver.getLat()) + ", " + QString::number(driver.getLon()) + ")");
    scoreLabel->setText("Score: " + QString::number(driver.getScore()));

    // Set color by status
    if (driver.getStatus() == "baby")
        setStyleSheet("background-color: #FFCCCC;");
    else if (driver.getStatus() == "grown-up")
        setStyleSheet("background-color: #FFFFCC;");
    else
        setStyleSheet("background-color: #CCFFCC;");

    // Update reports list
    reportsList->clear();
    auto reports = service->getReportsInRadius(driver.getLat(), driver.getLon(), radius);
    for (const auto& r : reports) {
        QString item = QString::fromStdString(r.getDescription()) +
            " [" + QString::fromStdString(r.getReporter()) + "] " +
            (r.isValidated() ? "(VALIDATED)" : "");
        reportsList->addItem(item);
    }
}

void DriverWindow::onAddReport() {
    std::string desc = descEdit->text().toStdString();
    double lat = latEdit->text().toDouble();
    double lon = lonEdit->text().toDouble();
    if (desc.empty()) {
        QMessageBox::warning(this, "Error", "Description cannot be empty.");
        return;
    }
    if (distance(driver.getLat(), driver.getLon(), lat, lon) > 20) {
        QMessageBox::warning(this, "Error", "Report location too far from your location.");
        return;
    }
    try {
        service->addReport(desc, driver.getName(), lat, lon);
        descEdit->clear(); latEdit->clear(); lonEdit->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void DriverWindow::onValidateReport() {
    int idx = reportsList->currentRow();
    if (idx < 0) return;
    auto reports = service->getReportsInRadius(driver.getLat(), driver.getLon(), radius);
    if (idx >= (int)reports.size()) return;
    try {
        service->validateReport(reports[idx], driver.getName());
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void DriverWindow::onRadiusChanged(int value) {
    radius = value;
    refresh();
}

void DriverWindow::moveDriver(int dLat, int dLon) {
    service->moveDriver(driver.getName(), dLat, dLon);
}

// --- MapWindow Implementation ---

MapWindow::MapWindow(Service* service, QWidget* parent)
    : QWidget(parent), service(service)
{
    setWindowTitle("Waze-ing Map");
    setMinimumSize(400, 400);
    connect(service, &Service::dataChanged, this, QOverload<>::of(&MapWindow::update));
}

void MapWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    auto drivers = service->getAllDrivers();
    for (const auto& d : drivers) {
        int x = 50 + (int)(d.getLon() * 10);
        int y = 350 - (int)(d.getLat() * 10);
        painter.setBrush(Qt::blue);
        painter.drawEllipse(QPoint(x, y), 10, 10);
        painter.drawText(x + 12, y, QString::fromStdString(d.getName()));
    }
}

// --- Main GUI Setup ---

void startGUI(Service& service, QApplication& app) {
    std::vector<DriverWindow*> driverWindows;
    auto drivers = service.getAllDrivers();
    for (const auto& d : drivers) {
        auto* win = new DriverWindow(d, &service);
        win->show();
        driverWindows.push_back(win);
    }
    MapWindow* mapWin = new MapWindow(&service);
    mapWin->show();

    QObject::connect(&app, &QApplication::aboutToQuit, [&service]() {
        service.saveAll();
    });
}