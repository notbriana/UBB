#include "GUI.h"
#include <QMessageBox>
#include <algorithm>
#include <sstream>

PersonWindow::PersonWindow(Service& service, const Person& person, QWidget* parent)
    : QWidget(parent), service(service), person(person) {
    setupUI();
    connectSignals();
    service.addObserver(this);
    update();
    setWindowTitle(QString::fromStdString(person.getName()));
}

void PersonWindow::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    locationLabel = new QLabel(this);
    mainLayout->addWidget(locationLabel);

    nearCheck = new QCheckBox("Show only nearby events", this);
    mainLayout->addWidget(nearCheck);

    eventList = new QListWidget(this);
    mainLayout->addWidget(eventList);

    descriptionLabel = new QLabel(this);
    mainLayout->addWidget(descriptionLabel);

    if (person.getIsOrganiser()) {
        // Add event controls
        QGroupBox* addBox = new QGroupBox("Add Event", this);
        QVBoxLayout* addLayout = new QVBoxLayout(addBox);
        nameEdit = new QLineEdit(addBox);
        latEdit = new QLineEdit(addBox);
        lonEdit = new QLineEdit(addBox);
        newDescEdit = new QTextEdit(addBox);
        newDateEdit = new QLineEdit(addBox);
        addEventButton = new QPushButton("Add Event", addBox);
        addLayout->addWidget(new QLabel("Name:"));
        addLayout->addWidget(nameEdit);
        addLayout->addWidget(new QLabel("Latitude:"));
        addLayout->addWidget(latEdit);
        addLayout->addWidget(new QLabel("Longitude:"));
        addLayout->addWidget(lonEdit);
        addLayout->addWidget(new QLabel("Description:"));
        addLayout->addWidget(newDescEdit);
        addLayout->addWidget(new QLabel("Date:"));
        addLayout->addWidget(newDateEdit);
        addLayout->addWidget(addEventButton);
        mainLayout->addWidget(addBox);

        // Update event controls
        QGroupBox* updateBox = new QGroupBox("Update Selected Event", this);
        QVBoxLayout* updateLayout = new QVBoxLayout(updateBox);
        descriptionEdit = new QTextEdit(updateBox);
        dateEdit = new QLineEdit(updateBox);
        updateEventButton = new QPushButton("Update Event", updateBox);
        attendeesList = new QListWidget(updateBox);
        updateLayout->addWidget(new QLabel("Description:"));
        updateLayout->addWidget(descriptionEdit);
        updateLayout->addWidget(new QLabel("Date:"));
        updateLayout->addWidget(dateEdit);
        updateLayout->addWidget(updateEventButton);
        updateLayout->addWidget(new QLabel("Attendees:"));
        updateLayout->addWidget(attendeesList);
        mainLayout->addWidget(updateBox);
    } else {
        goingButton = new QPushButton("Going", this);
        mainLayout->addWidget(goingButton);
    }
}

void PersonWindow::connectSignals() {
    connect(eventList, &QListWidget::currentRowChanged, this, &PersonWindow::onEventSelectionChanged);
    connect(nearCheck, &QCheckBox::checkStateChanged, this, &PersonWindow::onNearCheckChanged);
    if (person.getIsOrganiser()) {
        connect(addEventButton, &QPushButton::clicked, this, &PersonWindow::onAddEventClicked);
        connect(updateEventButton, &QPushButton::clicked, this, &PersonWindow::onUpdateEventClicked);
    } else {
        connect(goingButton, &QPushButton::clicked, this, &PersonWindow::onGoingClicked);
    }
}

void PersonWindow::update() {
    locationLabel->setText(QString("Location: %1, %2")
        .arg(person.getLocation().latitude).arg(person.getLocation().longitude));

    eventList->clear();
    std::vector<Event> events = nearCheck->isChecked()
        ? service.getEventsNear(person, 5.0)
        : service.getEventsSortedByDate();

    for (const auto& ev : events) {
        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(ev.getName() + " | " + ev.getOrganiser() + " | " + ev.getDate()), eventList);
        if (person.getIsOrganiser() && ev.getOrganiser() == person.getName())
            item->setBackground(Qt::green);
        item->setData(Qt::UserRole, QString::fromStdString(ev.getName()));
    }
    descriptionLabel->clear();
    if (attendeesList) attendeesList->clear();
    if (descriptionEdit) descriptionEdit->clear();
    if (dateEdit) dateEdit->clear();
}

void PersonWindow::onEventSelectionChanged() {
    int idx = eventList->currentRow();
    if (idx < 0) return;
    std::vector<Event> events = nearCheck->isChecked()
        ? service.getEventsNear(person, 5.0)
        : service.getEventsSortedByDate();
    if (idx >= (int)events.size()) return;
    const Event& ev = events[idx];

    if (person.getIsOrganiser()) {
        descriptionEdit->setText(QString::fromStdString(ev.getDescription()));
        dateEdit->setText(QString::fromStdString(ev.getDate()));
        attendeesList->clear();
        for (const auto& att : ev.getAttendees())
            attendeesList->addItem(QString::fromStdString(att));
    } else {
        descriptionLabel->setText(QString::fromStdString(ev.getDescription()));
        goingButton->setEnabled(!ev.isAttending(person.getName()));
    }
}

void PersonWindow::onNearCheckChanged(int) {
    update();
}

void PersonWindow::onGoingClicked() {
    int idx = eventList->currentRow();
    if (idx < 0) return;
    std::vector<Event> events = nearCheck->isChecked()
        ? service.getEventsNear(person, 5.0)
        : service.getEventsSortedByDate();
    if (idx >= (int)events.size()) return;
    try {
        service.attendEvent(person.getName(), events[idx].getName());
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void PersonWindow::onAddEventClicked() {
    try {
        std::string name = nameEdit->text().toStdString();
        double lat = latEdit->text().toDouble();
        double lon = lonEdit->text().toDouble();
        std::string desc = newDescEdit->toPlainText().toStdString();
        std::string date = newDateEdit->text().toStdString();
        Event ev(person.getName(), name, desc, {lat, lon}, date);
        service.addEvent(ev);
        nameEdit->clear(); latEdit->clear(); lonEdit->clear();
        newDescEdit->clear(); newDateEdit->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void PersonWindow::onUpdateEventClicked() {
    int idx = eventList->currentRow();
    if (idx < 0) return;
    std::vector<Event> events = nearCheck->isChecked()
        ? service.getEventsNear(person, 5.0)
        : service.getEventsSortedByDate();
    if (idx >= (int)events.size()) return;
    try {
        std::string newDesc = descriptionEdit->toPlainText().toStdString();
        std::string newDate = dateEdit->text().toStdString();
        service.updateEvent(events[idx].getName(), newDesc, newDate);
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

// --- PopularEventsWindow ---

PopularEventsWindow::PopularEventsWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setupUI();
    service.addObserver(this);
    update();
    setWindowTitle("Popular Events");
}

void PopularEventsWindow::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    popularList = new QListWidget(this);
    layout->addWidget(popularList);
}

void PopularEventsWindow::update() {
    popularList->clear();
    auto events = service.getPopularEvents();
    for (const auto& ev : events) {
        std::ostringstream oss;
        oss << ev.getName() << " | " << ev.getDescription() << " | "
            << ev.getLocation().latitude << "," << ev.getLocation().longitude << " | "
            << ev.getDate() << " | " << ev.getAttendees().size() << " going";
        popularList->addItem(QString::fromStdString(oss.str()));
    }
}