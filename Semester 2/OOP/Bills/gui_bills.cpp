#include "gui_bills.h"
#include <QColor>
#include <QBrush>

gui_bills::gui_bills(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Bills Manager");
    this->resize(600, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    // Initialize all widgets
    this->billsListWidget = new QListWidget;
    this->sortBills = new QPushButton("Sort the bills");

    // Filter section
    this->filterLabel = new QLabel("Filter bills:");
    this->showAllCheckBox = new QCheckBox("Show All");
    this->showPaidCheckBox = new QCheckBox("Show Paid Only");
    this->showUnpaidCheckBox = new QCheckBox("Show Unpaid Only");

    // Set initial filter state
    this->showAllCheckBox->setChecked(true);

    // Company input section
    this->userInputLabel = new QLabel("Enter the name of the company:");
    this->userInput = new QLineEdit;
    this->calculateAmountOfUnpaidBill = new QPushButton("Calculate amount of unpaid bills");
    this->calculateAmountLabel = new QLabel("Total amount of unpaid bills:");
    this->totalAmount = new QLineEdit;
    this->totalAmount->setReadOnly(true);

    // Create filter layout
    QHBoxLayout* filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(showAllCheckBox);
    filterLayout->addWidget(showPaidCheckBox);
    filterLayout->addWidget(showUnpaidCheckBox);
    filterLayout->addStretch();

    // Add widgets to the main layout
    mainLayout->addWidget(billsListWidget);
    mainLayout->addWidget(sortBills);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(userInputLabel);
    mainLayout->addWidget(userInput);
    mainLayout->addWidget(calculateAmountOfUnpaidBill);
    mainLayout->addWidget(calculateAmountLabel);
    mainLayout->addWidget(totalAmount);

    // Create central widget and set the layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

    // Connect signals to slots
    connect(sortBills, &QPushButton::clicked, this, &gui_bills::loadSortedBills);
    connect(calculateAmountOfUnpaidBill, &QPushButton::clicked, this, &gui_bills::showAmountOfBills);

    // Connect filter checkboxes
    connect(showAllCheckBox, &QCheckBox::toggled, this, &gui_bills::filterBills);
    connect(showPaidCheckBox, &QCheckBox::toggled, this, &gui_bills::filterBills);
    connect(showUnpaidCheckBox, &QCheckBox::toggled, this, &gui_bills::filterBills);

    // Load initial bills list (sorted by company name)
    this->loadSortedBills();
}

gui_bills::~gui_bills()
{
}

void gui_bills::loadBills()
{
    updateBillsList(this->service.getBills());
}

void gui_bills::loadSortedBills()
{
    updateBillsList(this->service.getBillsSorted());
}

void gui_bills::updateBillsList(const std::vector<bills>& billsToShow)
{
    this->billsListWidget->clear();

    for (const auto& bill : billsToShow) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));

        // Set red background for unpaid bills
        if (!bill.getIsPaid()) {
            item->setBackground(QBrush(QColor(255, 200, 200))); // Light red background
            item->setForeground(QBrush(QColor(139, 0, 0))); // Dark red text
        }

        this->billsListWidget->addItem(item);
    }
}

void gui_bills::showAmountOfBills()
{
    std::string company = this->userInput->text().toStdString();

    if (company.empty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a company name.");
        return;
    }

    if (!this->service.companyExists(company)) {
        QMessageBox::warning(this, "Company Not Found",
            QString("No bills found for company: %1").arg(QString::fromStdString(company)));
        this->totalAmount->clear();
        return;
    }

    double amount = this->service.calculateAmountOfBillsFromCompany(company);
    this->totalAmount->setText(QString::number(amount, 'f', 2));

    if (amount == 0.0) {
        QMessageBox::information(this, "No Unpaid Bills",
            QString("Company %1 has no unpaid bills.").arg(QString::fromStdString(company)));
    }
}

void gui_bills::filterBills()
{
    // Ensure only one checkbox is selected at a time
    QCheckBox* sender = qobject_cast<QCheckBox*>(QObject::sender());

    if (sender && sender->isChecked()) {
        if (sender == showAllCheckBox) {
            showPaidCheckBox->setChecked(false);
            showUnpaidCheckBox->setChecked(false);
            updateBillsList(service.getBillsSorted());
        }
        else if (sender == showPaidCheckBox) {
            showAllCheckBox->setChecked(false);
            showUnpaidCheckBox->setChecked(false);
            updateBillsList(service.getPaidBills());
        }
        else if (sender == showUnpaidCheckBox) {
            showAllCheckBox->setChecked(false);
            showPaidCheckBox->setChecked(false);
            updateBillsList(service.getUnpaidBills());
        }
    }
    else if (sender && !sender->isChecked()) {
        // If user unchecks current selection, default to "Show All"
        showAllCheckBox->setChecked(true);
        showPaidCheckBox->setChecked(false);
        showUnpaidCheckBox->setChecked(false);
        updateBillsList(service.getBillsSorted());
    }
}