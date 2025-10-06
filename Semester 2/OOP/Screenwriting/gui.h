#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QStandardItemModel>
#include "service.h"

class WriterWindow : public QWidget {
    Q_OBJECT
    Service& service;
    Writer writer;
    QTableView* table;
    QStandardItemModel* model;
    QLineEdit* descEdit;
    QLineEdit* actEdit;
    QPushButton* addBtn;
    QPushButton* acceptBtn;
    QPushButton* developBtn;
    QPushButton* savePlotBtn;
    std::vector<QTextEdit*> devEdits;
    std::vector<QPushButton*> saveDevBtns;
    void loadIdeas();
    void setupUI();
    void connectSignals();
    void showDevelopWindows();
public:
    WriterWindow(Service& s, const Writer& w, QWidget* parent = nullptr);
};