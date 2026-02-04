#include "gui_car.h"
#include <QColor>
#include <QBrush>
#include <algorithm>

GuiCar::GuiCar(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Car Manager");
    this->resize(800, 600);

    // Create main splitter for two-panel layout
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Left panel - All cars
    QWidget* leftPanel = new QWidget;
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    this->allCarsLabel = new QLabel("All Cars (sorted by manufacturer):");
    this->allCarsListWidget = new QListWidget;

    leftLayout->addWidget(allCarsLabel);
    leftLayout->addWidget(allCarsListWidget);

    // Right panel - Manufacturer search
    QWidget* rightPanel = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    this->manufacturerInputLabel = new QLabel("Enter manufacturer name:");
    this->manufacturerInput = new QLineEdit;
    this->showCarsButton = new QPushButton("Show cars");

    this->manufacturerCarsLabel = new QLabel("Cars from selected manufacturer:");
    this->manufacturerCarsListWidget = new QListWidget;

    this->carCountLabel = new QLabel("Number of cars:");
    this->carCountDisplay = new QLineEdit;
    this->carCountDisplay->setReadOnly(true);

    // Add widgets to right layout
    rightLayout->addWidget(manufacturerInputLabel);
    rightLayout->addWidget(manufacturerInput);
    rightLayout->addWidget(showCarsButton);
    rightLayout->addWidget(manufacturerCarsLabel);
    rightLayout->addWidget(manufacturerCarsListWidget);
    rightLayout->addWidget(carCountLabel);
    rightLayout->addWidget(carCountDisplay);

    // Add panels to splitter
    mainSplitter->addWidget(leftPanel);
    mainSplitter->addWidget(rightPanel);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 1);

    // Set central widget
    this->setCentralWidget(mainSplitter);

    // Connect signals to slots
    connect(showCarsButton, &QPushButton::clicked, this, &GuiCar::showCarsByManufacturer);
    connect(manufacturerInput, &QLineEdit::returnPressed, this, &GuiCar::showCarsByManufacturer);

    // Load initial cars list (sorted by manufacturer)
    this->loadAllCars();
}

GuiCar::~GuiCar()
{
}

void GuiCar::loadAllCars()
{
    updateCarsList(this->allCarsListWidget, this->service.getCarsSorted());
}

void GuiCar::updateCarsList(QListWidget* listWidget, const std::vector<Car>& carsToShow)
{
    listWidget->clear();

    for (const auto& car : carsToShow) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(car.toString()));

        // Set font color to match car's color
        QColor carColor = car.getQColor();
        item->setForeground(QBrush(carColor));

        // If color is too light (like white/yellow), add a darker background for visibility
        if (carColor == Qt::white || carColor == Qt::yellow) {
            item->setBackground(QBrush(QColor(240, 240, 240))); // Light gray background
        }

        listWidget->addItem(item);
    }
}

void GuiCar::showCarsByManufacturer()
{
    std::string manufacturer = this->manufacturerInput->text().toStdString();

    if (manufacturer.empty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a manufacturer name.");
        return;
    }

    if (!this->service.manufacturerExists(manufacturer)) {
        QMessageBox::warning(this, "Manufacturer Not Found",
            QString("No cars found for manufacturer: %1").arg(QString::fromStdString(manufacturer)));
        this->manufacturerCarsListWidget->clear();
        this->carCountDisplay->clear();
        return;
    }

    // Get cars by manufacturer
    std::vector<Car> manufacturerCars = this->service.getCarsByManufacturer(manufacturer);
    updateCarsList(this->manufacturerCarsListWidget, manufacturerCars);

    // Get and display count
    int count = this->service.getNumberOfCarsByManufacturer(manufacturer);
    this->carCountDisplay->setText(QString::number(count));

    // Update label to show current manufacturer
    this->manufacturerCarsLabel->setText(QString("Cars from %1:").arg(QString::fromStdString(manufacturer)));
}