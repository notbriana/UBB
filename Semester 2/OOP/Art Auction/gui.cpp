#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

AuctionGUI::AuctionGUI(AuctionService& s, int uid, QWidget* parent)
    : QWidget(parent), service(s), userId(uid)
{
    service.addObserver(this);
    setupUI();
    connectSignals();
    refreshCategories();
    refreshItems();
}

AuctionGUI::~AuctionGUI() {
    service.removeObserver(this);
}

void AuctionGUI::setupUI() {
    auto* mainLayout = new QVBoxLayout(this);
    categoryCombo = new QComboBox(this);
    mainLayout->addWidget(new QLabel("Category:", this));
    mainLayout->addWidget(categoryCombo);

    itemsList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("Items:", this));
    mainLayout->addWidget(itemsList);

    itemDetails = new QLabel(this);
    mainLayout->addWidget(itemDetails);

    offersList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("Offers (user id, sum, date):", this));
    mainLayout->addWidget(offersList);

    QHBoxLayout* bidLayout = new QHBoxLayout();
    offerInput = new QLineEdit(this);
    offerInput->setPlaceholderText("Enter your offer");
    bidButton = new QPushButton("Bid", this);
    bidLayout->addWidget(offerInput);
    bidLayout->addWidget(bidButton);
    mainLayout->addLayout(bidLayout);

    statusLabel = new QLabel(this);
    mainLayout->addWidget(statusLabel);

    // Add item UI (only for administrators)
    if (service.getUserType(userId) == UserType::Administrator) {
        QHBoxLayout* addItemLayout = new QHBoxLayout();
        addItemName = new QLineEdit(this);
        addItemName->setPlaceholderText("Item name");
        addItemCategory = new QLineEdit(this);
        addItemCategory->setPlaceholderText("Category");
        addItemPrice = new QLineEdit(this);
        addItemPrice->setPlaceholderText("Current price");
        addItemButton = new QPushButton("Add Item", this);
        addItemLayout->addWidget(addItemName);
        addItemLayout->addWidget(addItemCategory);
        addItemLayout->addWidget(addItemPrice);
        addItemLayout->addWidget(addItemButton);
        static_cast<QVBoxLayout*>(layout())->addLayout(addItemLayout);
    }
}

void AuctionGUI::connectSignals() {
    connect(categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AuctionGUI::onCategoryChanged);
    connect(itemsList, &QListWidget::itemSelectionChanged, this, &AuctionGUI::onItemSelected);
    connect(bidButton, &QPushButton::clicked, this, &AuctionGUI::onBid);
    if (addItemButton)
        connect(addItemButton, &QPushButton::clicked, this, &AuctionGUI::onAddItem);
}

void AuctionGUI::refreshCategories() {
    categoryCombo->clear();
    categoryCombo->addItem("All"); // Add "All" option first
    auto cats = service.getCategories();
    for (const auto& cat : cats)
        categoryCombo->addItem(QString::fromStdString(cat));
}

void AuctionGUI::refreshItems() {
    itemsList->clear();
    auto items = service.getItems();

    // Get selected category
    std::string selectedCat;
    if (categoryCombo->currentIndex() >= 0)
        selectedCat = categoryCombo->currentText().toStdString();

    // Sort items by currentPrice ascending
    std::vector<Item> sortedItems;
    for (const auto& item : items) {
        // Show all items if "All" is selected, otherwise filter by category
        if (selectedCat == "All" || item.category == selectedCat)
            sortedItems.push_back(item);
    }
    std::sort(sortedItems.begin(), sortedItems.end(), [](const Item& a, const Item& b) {
        return a.currentPrice < b.currentPrice;
    });

    // Show filtered and sorted items
    for (const auto& item : sortedItems) {
        itemsList->addItem(QString::fromStdString(
            item.name + " | " + item.category + " | Price: " + std::to_string(item.currentPrice)
        ));
    }
    offersList->clear();
    itemDetails->clear();
}

void AuctionGUI::refreshOffers() {
    offersList->clear();
    QListWidgetItem* selected = itemsList->currentItem();
    if (!selected) return;
    QString itemText = selected->text();
    std::string itemName = itemText.split(" | ").first().toStdString();
    const auto& items = service.getItems();
    auto it = std::find_if(items.begin(), items.end(), [&](const Item& i) { return i.name == itemName; });
    if (it == items.end()) return;
    std::vector<Offer> sortedOffers = it->offers;
    std::sort(sortedOffers.begin(), sortedOffers.end(), [](const Offer& a, const Offer& b) {
        return a.date > b.date;
    });
    for (const auto& offer : sortedOffers) {
        offersList->addItem(QString("User ID: %1, Sum: %2, Date: %3")
            .arg(offer.userId)
            .arg(offer.offeredSum)
            .arg(QString::fromStdString(offer.date)));
    }
}

void AuctionGUI::showItemDetails() {
    QListWidgetItem* selected = itemsList->currentItem();
    if (!selected) {
        itemDetails->clear();
        return;
    }
    std::string itemName = selected->text().toStdString();
    const auto& items = service.getItems();
    auto it = std::find_if(items.begin(), items.end(), [&](const Item& i) { return i.name == itemName; });
    if (it == items.end()) {
        itemDetails->clear();
        return;
    }
    itemDetails->setText(QString("Name: %1\nCategory: %2\nCurrent Price: %3")
        .arg(QString::fromStdString(it->name))
        .arg(QString::fromStdString(it->category))
        .arg(it->currentPrice));
}

void AuctionGUI::update() {
    refreshCategories();
    refreshItems();
    refreshOffers();
    showItemDetails();
}

void AuctionGUI::onCategoryChanged(int) {
    refreshItems();
}

void AuctionGUI::onItemSelected() {
    refreshOffers();
    showItemDetails();
}

void AuctionGUI::onBid() {
    QListWidgetItem* sel = itemsList->currentItem();
    if (!sel) {
        statusLabel->setText("Select an item.");
        return;
    }
    bool ok;
    double sum = offerInput->text().toDouble(&ok);
    if (!ok) {
        statusLabel->setText("Invalid sum.");
        return;
    }
    QString itemText = sel->text();
    QString itemName = itemText.section(" | ", 0, 0); // Extract only the name
    QString date = QDate::currentDate().toString(Qt::ISODate);
    try {
        service.addOffer(itemName.toStdString(), userId, sum, date.toStdString());
        statusLabel->setText("Offer added.");
    }
    catch (std::exception& e) {
        statusLabel->setText(e.what());
    }
    offerInput->clear();
    refreshOffers();
}

void AuctionGUI::onAddItem() {
    QString name = addItemName->text();
    QString category = addItemCategory->text();
    bool ok;
    double price = addItemPrice->text().toDouble(&ok);

    if (name.trimmed().isEmpty()) {
        statusLabel->setText("Error: Name cannot be empty.");
        return;
    }
    if (!ok || price <= 0) {
        statusLabel->setText("Error: Price must be positive.");
        return;
    }
    try {
        service.addItem(name.toStdString(), category.toStdString(), price);
        statusLabel->setText("Item added.");
        addItemName->clear();
        addItemCategory->clear();
        addItemPrice->clear();
    } catch (const std::exception& e) {
        statusLabel->setText(e.what());
    }
}