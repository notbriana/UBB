#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <cmath>

static double euclidean(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2, dy = y1 - y2;
    return std::sqrt(dx*dx + dy*dy);
}

// ---------------- DriverWindow ----------------

DriverWindow::DriverWindow(Service& service, const Driver& driver, QWidget* parent)
    : QWidget(parent), service(service), driver(driver)
{
    setWindowTitle(QString::fromStdString(driver.name));
    QVBoxLayout* mainLayout = new QVBoxLayout;

    locationLabel = new QLabel;
    scoreLabel = new QLabel;
    mainLayout->addWidget(locationLabel);
    mainLayout->addWidget(scoreLabel);

    reportsList = new QListWidget;
    mainLayout->addWidget(new QLabel("Nearby Reports:"));
    mainLayout->addWidget(reportsList);

    validateButton = new QPushButton("Validate Selected Report");
    mainLayout->addWidget(validateButton);

    QHBoxLayout* reportInputLayout = new QHBoxLayout;
    reportDescInput = new QLineEdit;
    reportDescInput->setPlaceholderText("Description");
    reportLatInput = new QLineEdit;
    reportLatInput->setPlaceholderText("Latitude");
    reportLonInput = new QLineEdit;
    reportLonInput->setPlaceholderText("Longitude");
    addReportButton = new QPushButton("Add Report");
    reportInputLayout->addWidget(reportDescInput);
    reportInputLayout->addWidget(reportLatInput);
    reportInputLayout->addWidget(reportLonInput);
    reportInputLayout->addWidget(addReportButton);
    mainLayout->addLayout(reportInputLayout);

    chatList = new QListWidget;
    mainLayout->addWidget(new QLabel("Chat:"));
    mainLayout->addWidget(chatList);

    QHBoxLayout* chatLayout = new QHBoxLayout;
    chatInput = new QLineEdit;
    sendButton = new QPushButton("Send");
    chatLayout->addWidget(chatInput);
    chatLayout->addWidget(sendButton);
    mainLayout->addLayout(chatLayout);

    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &DriverWindow::sendMessage);
    connect(addReportButton, &QPushButton::clicked, this, &DriverWindow::addReport);
    connect(validateButton, &QPushButton::clicked, this, &DriverWindow::validateReport);

    service.addObserver(this);
    update();
}

void DriverWindow::refreshReports() {
    reportsList->clear();
    const auto& reports = service.getReports();
    for (size_t i = 0; i < reports.size(); ++i) {
        const auto& r = reports[i];
        double dist = euclidean(driver.latitude, driver.longitude, r.latitude, r.longitude);
        if (dist <= 10.0) {
            QString text = QString("[%1] %2 (%3, %4) by %5")
                .arg(r.validated ? "VALID" : "PENDING")
                .arg(QString::fromStdString(r.description))
                .arg(r.latitude).arg(r.longitude)
                .arg(QString::fromStdString(r.reporter));
            QListWidgetItem* item = new QListWidgetItem(text);
            if (r.validated)
                item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
            reportsList->addItem(item);
        }
    }
}

void DriverWindow::refreshChat() {
    chatList->clear();
    for (const auto& msg : service.getChat()) {
        chatList->addItem(QString::fromStdString(msg.sender + ": " + msg.text));
    }
}

void DriverWindow::refreshScore() {
    // Find the up-to-date driver by name
    const auto& drivers = service.getDrivers();
    for (const auto& d : drivers) {
        if (d.getName() == driver.name) {
            scoreLabel->setText(QString("Score: %1").arg(d.getScore()));
            return;
        }
    }
    // If not found, fallback (should not happen)
    scoreLabel->setText("Score: ?");
}

void DriverWindow::update() {
    // Find the up-to-date driver by name
    const auto& drivers = service.getDrivers();
    for (const auto& d : drivers) {
        if (d.getName() == driver.name) {
            locationLabel->setText(QString("Location: (%1, %2)").arg(d.getLatitude()).arg(d.getLongitude()));
            break;
        }
    }
    refreshScore();
    refreshReports();
    refreshChat();
}

void DriverWindow::sendMessage() {
    QString text = chatInput->text();
    if (text.isEmpty()) return;
    Message msg{ driver.name, text.toStdString() };
    service.addMessage(msg);
    chatInput->clear();
}

void DriverWindow::addReport() {
    QString desc = reportDescInput->text();
    bool ok1, ok2;
    double lat = reportLatInput->text().toDouble(&ok1);
    double lon = reportLonInput->text().toDouble(&ok2);
    if (desc.isEmpty() || !ok1 || !ok2) {
        QMessageBox::warning(this, "Error", "Invalid input for report.");
        return;
    }
    double dist = euclidean(driver.latitude, driver.longitude, lat, lon);
    if (dist > 20.0) {
        QMessageBox::warning(this, "Error", "Report location too far from your position.");
        return;
    }
    Report r{ desc.toStdString(), driver.name, lat, lon, false, {} };
    service.addReport(r);
    reportDescInput->clear();
    reportLatInput->clear();
    reportLonInput->clear();
}

void DriverWindow::validateReport() {
    int idx = reportsList->currentRow();
    if (idx < 0) return;
    // Find the idx-th report in the filtered list
    int count = -1;
    const auto& reports = service.getReports();
    for (size_t i = 0; i < reports.size(); ++i) {
        double dist = euclidean(driver.latitude, driver.longitude, reports[i].latitude, reports[i].longitude);
        if (dist <= 10.0) {
            ++count;
            if (count == idx) {
                service.validateReport(static_cast<int>(i), driver.name);
                refreshScore(); // Refresh score after validation
                break;
            }
        }
    }
}

// ---------------- MapWindow ----------------

MapWindow::MapWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service)
{
    setWindowTitle("Map of Valid Reports");
    resize(400, 400);
    service.addObserver(this);
}

void MapWindow::update() {
    repaint();
}

void MapWindow::paintEvent(QPaintEvent*) {
    QPainter p(this);
    const auto& reports = service.getReports();
    int w = width(), h = height();

    // Find min/max for normalization
    double minLat = 1e9, maxLat = -1e9, minLon = 1e9, maxLon = -1e9;
    for (const auto& r : reports) {
        if (r.validated) {
            if (r.latitude < minLat) minLat = r.latitude;
            if (r.latitude > maxLat) maxLat = r.latitude;
            if (r.longitude < minLon) minLon = r.longitude;
            if (r.longitude > maxLon) maxLon = r.longitude;
        }
    }
    if (minLat == maxLat) { minLat -= 1; maxLat += 1; }
    if (minLon == maxLon) { minLon -= 1; maxLon += 1; }

    for (const auto& r : reports) {
        if (!r.validated) continue;
        // Normalize lat/lon to widget coordinates
        int x = static_cast<int>(((r.latitude - minLat) / (maxLat - minLat)) * (w - 40) + 20);
        int y = static_cast<int>(((r.longitude - minLon) / (maxLon - minLon)) * (h - 40) + 20);
        p.setBrush(Qt::green);
        p.drawEllipse(QPoint(x, y), 10, 10);
        p.drawText(x + 12, y, QString::fromStdString(r.description));
    }
}