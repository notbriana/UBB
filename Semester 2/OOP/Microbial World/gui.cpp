#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>

void BacteriaTableModel::setBacteria(const QVector<Bacterium>& b) {
    beginResetModel();
    bacteria = b;
    endResetModel();
}

int BacteriaTableModel::rowCount(const QModelIndex&) const { return bacteria.size(); }
int BacteriaTableModel::columnCount(const QModelIndex&) const { return 3; }
QVariant BacteriaTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= bacteria.size()) return {};
    const auto& b = bacteria[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0: return b.name;
            case 1: return b.species;
            case 2: return b.size;
        }
    }
    return {};
}
QVariant BacteriaTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
        case 0: return "Name";
        case 1: return "Species";
        case 2: return "Size";
    }
    return {};
}
Qt::ItemFlags BacteriaTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}
bool BacteriaTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole || !index.isValid() || index.row() >= bacteria.size()) return false;
    Bacterium oldBac = bacteria[index.row()];
    Bacterium newBac = oldBac;
    switch (index.column()) {
        case 0: newBac.name = value.toString(); break;
        case 1: newBac.species = value.toString(); break;
        case 2: newBac.size = value.toInt(); break;
    }
    // Update in the service (which will emit dataChanged and cause all views to refresh)
    if (service->updateBacterium(oldBac.name, oldBac.species, newBac)) {
        // Optionally update local cache, but it will be refreshed anyway
        return true;
    }
    return false;
}
Bacterium BacteriaTableModel::getBacterium(int row) const { return bacteria[row]; }

BiologistWindow::BiologistWindow(Service& s, const Biologist& b, QWidget* parent)
    : QWidget(parent), service(s), biologist(b) {
    setWindowTitle(biologist.name);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    speciesCombo = new QComboBox;
    mainLayout->addWidget(speciesCombo);

    model = new BacteriaTableModel(&service, this);
    table = new QTableView;
    table->setModel(model);
    mainLayout->addWidget(table);

    diseaseList = new QListWidget;
    mainLayout->addWidget(diseaseList);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    addBacteriumBtn = new QPushButton("Add Bacterium");
    addDiseaseBtn = new QPushButton("Add Disease");
    viewBtn = new QPushButton("View");
    btnLayout->addWidget(addBacteriumBtn);
    btnLayout->addWidget(addDiseaseBtn);
    btnLayout->addWidget(viewBtn);
    mainLayout->addLayout(btnLayout);

    refreshSpeciesCombo();
    refreshTable();

    connect(speciesCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int) {
        refreshTable();
    });
    connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [=](const QModelIndex& idx) {
        refreshDiseaseList(idx.row());
    });
    connect(addBacteriumBtn, &QPushButton::clicked, this, [=]() {
        QString name = QInputDialog::getText(this, "Name", "Bacterium name:");
        QString species = QInputDialog::getItem(this, "Species", "Species:", biologist.studiedSpecies);
        int size = QInputDialog::getInt(this, "Size", "Size:");
        QString diseases = QInputDialog::getText(this, "Diseases", "Diseases (comma separated):");
        QStringList rawList = diseases.split(',');
        QVector<QString> diseaseList;
        for (const QString& d : rawList) {
            if (!d.trimmed().isEmpty())
                diseaseList.append(d.trimmed());
        }
        if (!service.addBacterium(Bacterium(name, species, size, diseaseList)))
            QMessageBox::warning(this, "Error", "Duplicate bacterium!");
    });
    connect(addDiseaseBtn, &QPushButton::clicked, this, [=]() {
        auto idx = table->currentIndex();
        if (!idx.isValid()) {
            QMessageBox::warning(this, "No selection", "Please select a bacterium in the table first.");
            return;
        }
        QString disease = QInputDialog::getText(this, "Disease", "New disease:");
        if (disease.isEmpty()) return;
        auto b = model->getBacterium(idx.row());
        service.addDisease(b.name, b.species, disease);
    });
    connect(model, &BacteriaTableModel::bacteriumEdited, this, [=](int row, const Bacterium& b) {
        auto old = model->getBacterium(row);
        service.updateBacterium(old.name, old.species, b);
        refreshTable();
    });
    connect(&service, &Service::dataChanged, this, [=]() { refreshTable(); });

    connect(viewBtn, &QPushButton::clicked, this, [=]() {
        // Open a new window with custom paint (see below)
        class SpeciesView : public QWidget {
            QVector<Bacterium> bacteria;
        public:
            SpeciesView(const QVector<Bacterium>& b, QWidget* parent = nullptr)
                : QWidget(parent), bacteria(b) { setMinimumSize(400, 400); }
            void paintEvent(QPaintEvent*) override {
                QPainter p(this);
                QMap<QString, QVector<Bacterium>> bySpecies;
                for (const auto& b : bacteria) bySpecies[b.species].append(b);
                int y = 20;
                for (auto it = bySpecies.begin(); it != bySpecies.end(); ++it) {
                    p.drawText(20, y, it.key());
                    y += 20;
                    int x = 40;
                    for (const auto& b : it.value()) {
                        p.drawEllipse(x, y, 20, 20);
                        p.drawText(x, y + 35, b.name);
                        x += 50;
                    }
                    y += 60;
                }
            }
        };
        auto* w = new SpeciesView(service.getBacteriaForSpecies(biologist.studiedSpecies));
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
}

void BiologistWindow::refreshSpeciesCombo() {
    speciesCombo->clear();
    for (const auto& s : biologist.studiedSpecies)
        speciesCombo->addItem(s);
    speciesCombo->addItem("All");
}

void BiologistWindow::refreshTable() {
    QString selected = speciesCombo->currentText();
    QVector<Bacterium> bacs;
    if (selected == "All" || selected.isEmpty())
        bacs = service.getBacteriaForSpecies(biologist.studiedSpecies);
    else
        bacs = service.getBacteriaForSpecies({selected});
    model->setBacteria(bacs);
    if (!bacs.isEmpty())
        refreshDiseaseList(0);
    if (model->rowCount() > 0) {
        table->selectRow(0);
    }
}

void BiologistWindow::refreshDiseaseList(int row) {
    diseaseList->clear();
    if (row < 0 || row >= model->rowCount()) return;
    auto b = model->getBacterium(row);
    for (const auto& d : b.diseases)
        diseaseList->addItem(d);
}