#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <map>
#include <vector>

DoctorWindow::DoctorWindow(Service& s, const Doctor& d) : service(s), doctor(d) {
    setWindowTitle(QString::fromStdString(doctor.getName()));
    onlyMineBox = new QCheckBox("Only my patients");
    patientList = new QListWidget;
    addBtn = new QPushButton("Add Patient");
    updateBtn = new QPushButton("Update Patient");
    nameEdit = new QLineEdit; diagEdit = new QLineEdit; specEdit = new QLineEdit; dateEdit = new QLineEdit;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(onlyMineBox);
    layout->addWidget(patientList);
    QHBoxLayout* form = new QHBoxLayout;
    form->addWidget(nameEdit); form->addWidget(diagEdit); form->addWidget(specEdit); form->addWidget(dateEdit);
    layout->addLayout(form);
    layout->addWidget(addBtn); layout->addWidget(updateBtn);
    setLayout(layout);
    reload();
    connect(onlyMineBox, &QCheckBox::checkStateChanged, this, &DoctorWindow::reload);

    // When a patient is selected, fill the fields
    connect(patientList, &QListWidget::currentRowChanged, [this](int row) {
        if (row >= 0 && row < static_cast<int>(currentPatients.size())) {
            const auto& p = currentPatients[row];
            nameEdit->setText(QString::fromStdString(p.getName()));
            diagEdit->setText(QString::fromStdString(p.getDiagnosis()));
            specEdit->setText(QString::fromStdString(p.getNeededSpecialisation()));
            dateEdit->setText(QString::fromStdString(p.getAdmissionDate()));
        } else {
            nameEdit->clear();
            diagEdit->clear();
            specEdit->clear();
            dateEdit->clear();
        }
    });

    connect(addBtn, &QPushButton::clicked, [this]() {
        try {
            service.addPatient(Patient(
                nameEdit->text().toStdString(),
                diagEdit->text().isEmpty() ? "undiagnosed" : diagEdit->text().toStdString(),
                specEdit->text().toStdString(),
                "", // current doctor empty
                dateEdit->text().toStdString()
            ));
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });

    connect(updateBtn, &QPushButton::clicked, [this]() {
        int row = patientList->currentRow();
        if (row < 0 || row >= static_cast<int>(currentPatients.size())) {
            QMessageBox::warning(this, "Error", "No patient selected for update.");
            return;
        }
        try {
            // Use the selected patient's name for update
            service.updatePatient(
                currentPatients[row].getName(),
                diagEdit->text().toStdString(),
                specEdit->text().toStdString(),
                doctor.getName()
            );
        } catch (std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });
    service.addObserver(this);
}

void DoctorWindow::reload() {
    patientList->clear();
    bool onlyMine = onlyMineBox->isChecked();
    currentPatients = service.getPatientsForDoctor(doctor, onlyMine); // Store the current list
    for (const auto& p : currentPatients) {
        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(p.getName() + " | " + p.getDiagnosis() + " | " + p.getAdmissionDate())
        );
        if (p.getCurrentDoctor() == doctor.getName())
            item->setBackground(Qt::green);
        patientList->addItem(item);
    }
}

void DoctorWindow::update() { reload(); }

StatsWindow::StatsWindow(Service& s) : service(s) {
    setWindowTitle("Statistics");
    resize(400, 300);
    service.addObserver(this);
}

void StatsWindow::update() { repaint(); }

void StatsWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    std::map<std::string, int> counts;
    for (const auto& p : service.getPatients()) {
        std::string spec = p.getNeededSpecialisation();
        if (spec.empty()) spec = "undiagnosed";
        counts[spec]++;
    }
    int x = 10, y = 10, w = 50, h = 20;
    int maxCount = 1;
    for (const auto& kv : counts) if (kv.second > maxCount) maxCount = kv.second;
    for (const auto& kv : counts) {
        painter.drawRect(x, y, w * kv.second, h);
        painter.drawText(x, y + h / 2, QString::fromStdString(kv.first + ": " + std::to_string(kv.second)));
        y += h + 10;
    }
}