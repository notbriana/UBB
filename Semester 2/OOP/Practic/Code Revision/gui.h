#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QLineEdit>
class ProgrammerWindow : public QWidget {
    Q_OBJECT

private:
    CodeRevisionService& service;
    Programmer programmer;
    QListWidget* list;
    QLabel* label;
    QPushButton* reviseButton;
    QLineEdit* fileInput;
    QPushButton* addButton;
    QPushButton* statsButton;

 
public:
    ProgrammerWindow(CodeRevisionService& service, Programmer programmer);
    void updateView();

private slots:
    void handleRevise();
    void handleAddFile(); // add this line
    void showStatistics();

};