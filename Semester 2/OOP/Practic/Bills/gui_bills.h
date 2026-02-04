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
#include <QCheckBox>
#include <QMessageBox>

class gui_bills : public QMainWindow
{
    Q_OBJECT

public:
    gui_bills(QWidget* parent = nullptr);
    ~gui_bills();

private:
    Service service;

    // UI Elements
    QListWidget* billsListWidget;
    QPushButton* sortBills;
    QLabel* userInputLabel;
    QLineEdit* userInput;
    QPushButton* calculateAmountOfUnpaidBill;
    QLabel* calculateAmountLabel;
    QLineEdit* totalAmount;

    // Filter controls
    QLabel* filterLabel;
    QCheckBox* showAllCheckBox;
    QCheckBox* showPaidCheckBox;
    QCheckBox* showUnpaidCheckBox;

    void loadBills();
    void updateBillsList(const std::vector<bills>& billsToShow);

public slots:
    void loadSortedBills();
    void showAmountOfBills();
    void filterBills();
};