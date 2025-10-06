#pragma once

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "service.h"

class DriverWindow : public QWidget, public Observer {
    Q_OBJECT
    Service& service;
    Driver driver;

    QLabel* locationLabel;
    QLabel* scoreLabel;
    QListWidget* reportsList;
    QListWidget* chatList;
    QLineEdit* chatInput;
    QPushButton* sendButton;
    QLineEdit* reportDescInput;
    QLineEdit* reportLatInput;
    QLineEdit* reportLonInput;
    QPushButton* addReportButton;
    QPushButton* validateButton;

    void refreshReports();
    void refreshChat();

    void refreshScore();

public:
    DriverWindow(Service& service, const Driver& driver, QWidget* parent = nullptr);
    void update() override;

private slots:
    void sendMessage();
    void addReport();
    void validateReport();
};

class MapWindow : public QWidget, public Observer {
    Q_OBJECT
    Service& service;
public:
    MapWindow(Service& service, QWidget* parent = nullptr);
    void update() override;
protected:
    void paintEvent(QPaintEvent* event) override;
};