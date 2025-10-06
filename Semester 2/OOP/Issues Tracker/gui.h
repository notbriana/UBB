#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "service.h"
#include "domain.h"

class UserWindow : public QWidget {
    Q_OBJECT
    User user;
    Service& service;
    QListWidget* list;
    QLineEdit* descEdit;
    QPushButton* addBtn;
    QPushButton* removeBtn;
    QPushButton* resolveBtn;
    void populate();
public:
    UserWindow(const User& u, Service& s, QWidget* parent = nullptr);
private slots:
    void onAdd();
    void onRemove();
    void onResolve();
    void onSelectionChanged();
    void update();
};