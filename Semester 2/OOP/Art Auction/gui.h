#pragma once
#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "service.h"

class AuctionGUI : public QWidget, public Observer {
    Q_OBJECT
        AuctionService& service;
    int userId;

    // UI Elements
    QComboBox* categoryCombo;
    QListWidget* itemsList;
    QListWidget* offersList;
    QLabel* statusLabel;
    QLineEdit* offerInput;
    QPushButton* bidButton;
    QLabel* itemDetails;
    QLineEdit* addItemName = nullptr;
    QLineEdit* addItemCategory = nullptr;
    QLineEdit* addItemPrice = nullptr;
    QPushButton* addItemButton = nullptr;

public:
    AuctionGUI(AuctionService& service, int userId, QWidget* parent = nullptr);
    ~AuctionGUI();

    void update() override;

private:
    void setupUI();
    void connectSignals();
    void refreshCategories();
    void refreshItems();
    void refreshOffers();
    void showItemDetails();
private slots:
    void onCategoryChanged(int);
    void onItemSelected();
    void onBid();
    void onAddItem();
};