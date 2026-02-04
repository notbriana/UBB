#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QBrush>
#include <QColor>
#include "service.h"

class GuiEquation : public QWidget
{
    Q_OBJECT

private:
    EquationService service;

    // UI Components
    QListWidget* equationsList;
    QLineEdit* inputA;
    QLineEdit* inputB;
    QLineEdit* inputC;
    QPushButton* addButton;
    QPushButton* computeSolutionsButton;
    QTextEdit* solutionsDisplay;

    // Labels
    QLabel* equationsLabel;
    QLabel* addEquationLabel;
    QLabel* solutionsLabel;

public:
    GuiEquation(QWidget* parent = nullptr);

private slots:
    void populateEquationsList();
    void addEquation();
    void computeSolutions();
    void onEquationSelectionChanged();

private:
    void setupUI();
    void connectSignals();
};