#include "gui_equation.h"

GuiEquation::GuiEquation(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    connectSignals();
    populateEquationsList();
}

void GuiEquation::setupUI() {
    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // Equations list section
    equationsLabel = new QLabel("Quadratic Equations (Green = Real Solutions):");
    equationsLabel->setStyleSheet("font-weight: bold; font-size: 12px;");
    equationsList = new QListWidget();
    equationsList->setMinimumHeight(200);

    mainLayout->addWidget(equationsLabel);
    mainLayout->addWidget(equationsList);

    // Add equation section
    QGroupBox* addEquationGroup = new QGroupBox("Add New Equation");
    QHBoxLayout* addEquationLayout = new QHBoxLayout();

    addEquationLayout->addWidget(new QLabel("a:"));
    inputA = new QLineEdit();
    inputA->setPlaceholderText("Coefficient a");
    inputA->setMaximumWidth(80);
    addEquationLayout->addWidget(inputA);

    addEquationLayout->addWidget(new QLabel("b:"));
    inputB = new QLineEdit();
    inputB->setPlaceholderText("Coefficient b");
    inputB->setMaximumWidth(80);
    addEquationLayout->addWidget(inputB);

    addEquationLayout->addWidget(new QLabel("c:"));
    inputC = new QLineEdit();
    inputC->setPlaceholderText("Coefficient c");
    inputC->setMaximumWidth(80);
    addEquationLayout->addWidget(inputC);

    addButton = new QPushButton("Add Equation");
    addEquationLayout->addWidget(addButton);

    addEquationGroup->setLayout(addEquationLayout);
    mainLayout->addWidget(addEquationGroup);

    // Solutions section
    QGroupBox* solutionsGroup = new QGroupBox("Solutions");
    QVBoxLayout* solutionsLayout = new QVBoxLayout();

    computeSolutionsButton = new QPushButton("Compute Solutions");
    computeSolutionsButton->setEnabled(false);
    solutionsLayout->addWidget(computeSolutionsButton);

    solutionsDisplay = new QTextEdit();
    solutionsDisplay->setMaximumHeight(120);
    solutionsDisplay->setReadOnly(true);
    solutionsDisplay->setPlaceholderText("Select an equation and click 'Compute Solutions'");
    solutionsLayout->addWidget(solutionsDisplay);

    solutionsGroup->setLayout(solutionsLayout);
    mainLayout->addWidget(solutionsGroup);

    setLayout(mainLayout);
    setWindowTitle("Quadratic Equations Manager");
    setMinimumSize(600, 500);
}

void GuiEquation::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &GuiEquation::addEquation);
    connect(computeSolutionsButton, &QPushButton::clicked, this, &GuiEquation::computeSolutions);
    connect(equationsList, &QListWidget::currentRowChanged, this, &GuiEquation::onEquationSelectionChanged);

    // Enable add button when all fields have text
    connect(inputA, &QLineEdit::textChanged, [this]() {
        addButton->setEnabled(!inputA->text().isEmpty() && !inputB->text().isEmpty() && !inputC->text().isEmpty());
        });
    connect(inputB, &QLineEdit::textChanged, [this]() {
        addButton->setEnabled(!inputA->text().isEmpty() && !inputB->text().isEmpty() && !inputC->text().isEmpty());
        });
    connect(inputC, &QLineEdit::textChanged, [this]() {
        addButton->setEnabled(!inputA->text().isEmpty() && !inputB->text().isEmpty() && !inputC->text().isEmpty());
        });
}

void GuiEquation::populateEquationsList() {
    equationsList->clear();
    std::vector<Equation> equations = service.getAllEquations();

    for (const auto& equation : equations) {
        QString equationText = QString::fromStdString(equation.toMathematicalForm());
        QListWidgetItem* item = new QListWidgetItem(equationText);

        // Set green background for equations with real solutions
        if (equation.hasRealSolutions()) {
            item->setBackground(QBrush(QColor(144, 238, 144))); // Light green
        }

        equationsList->addItem(item);
    }
}

void GuiEquation::addEquation() {
    try {
        double a = inputA->text().toDouble();
        double b = inputB->text().toDouble();
        double c = inputC->text().toDouble();

        if (a == 0) {
            QMessageBox::warning(this, "Warning",
                "For a quadratic equation, coefficient 'a' should not be zero.\n"
                "This will be treated as a linear equation.");
        }

        service.addEquation(a, b, c);
        populateEquationsList();

        // Clear input fields
        inputA->clear();
        inputB->clear();
        inputC->clear();

        QMessageBox::information(this, "Success", "Equation added successfully!");

    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "Please enter valid numeric values for coefficients.");
    }
}

void GuiEquation::computeSolutions() {
    int currentRow = equationsList->currentRow();
    if (currentRow < 0) {
        return;
    }

    std::vector<Equation> equations = service.getAllEquations();
    if (currentRow >= static_cast<int>(equations.size())) {
        return;
    }

    const Equation& selectedEquation = equations[currentRow];
    std::string solutionsText = service.getSolutionsString(selectedEquation);

    solutionsDisplay->setPlainText(QString::fromStdString(solutionsText));
}

void GuiEquation::onEquationSelectionChanged() {
    bool hasSelection = equationsList->currentRow() >= 0;
    computeSolutionsButton->setEnabled(hasSelection);

    if (!hasSelection) {
        solutionsDisplay->clear();
        solutionsDisplay->setPlaceholderText("Select an equation and click 'Compute Solutions'");
    }
}

