#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QPainter>
#include <QHeaderView>

class ConstellationView : public QWidget {
    std::vector<Star> stars;
    Star selected;
public:
    ConstellationView(const std::vector<Star>& s, const Star& sel, QWidget* parent = nullptr)
        : QWidget(parent), stars(s), selected(sel) {}
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        int w = width(), h = height();
        for (const auto& star : stars) {
            int x = (star.ra % (w-40)) + 20;
            int y = (star.dec % (h-40)) + 20;
            p.setBrush(star.name == selected.name ? Qt::red : Qt::black);
            p.drawEllipse(QPoint(x, y), int(star.diameter), int(star.diameter));
        }
    }
};

AstronomerWindow::AstronomerWindow(Service& s, const Astronomer& a, QWidget* parent)
    : QWidget(parent), service(s), astronomer(a) {
    setupUI();
    connectSignals();
    setWindowTitle(QString::fromStdString(astronomer.name));
}

void AstronomerWindow::setupUI() {
    auto* layout = new QVBoxLayout(this);

    model = new StarModel(service);
    table = new QTableView;
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    filterBox = new QCheckBox("Show only my constellation");
    layout->addWidget(filterBox);

    auto* btnLayout = new QHBoxLayout;
    addBtn = new QPushButton("Add Star");
    updateBtn = new QPushButton("Update Star");
    viewBtn = new QPushButton("View");
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(updateBtn);
    btnLayout->addWidget(viewBtn);
    layout->addLayout(btnLayout);

    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Search stars by name...");
    searchList = new QListWidget;
    layout->addWidget(searchEdit);
    layout->addWidget(searchList);
}

void AstronomerWindow::connectSignals() {
    connect(filterBox, &QCheckBox::toggled, [=](bool checked) {
        model->setFilter(astronomer.constellation, checked);
    });

    connect(addBtn, &QPushButton::clicked, [=]() {
        QDialog dlg(this);
        dlg.setWindowTitle("Add Star");
        QFormLayout form(&dlg);

        QLineEdit nameEdit, raEdit, decEdit, diaEdit;
        form.addRow("Name:", &nameEdit);
        form.addRow("RA:", &raEdit);
        form.addRow("Dec:", &decEdit);
        form.addRow("Diameter:", &diaEdit);

        QPushButton ok("Add"), cancel("Cancel");
        QHBoxLayout btns;
        btns.addWidget(&ok); btns.addWidget(&cancel);
        form.addRow(&btns);

        connect(&ok, &QPushButton::clicked, [&]() {
            std::string name = nameEdit.text().toStdString();
            int ra = raEdit.text().toInt();
            int dec = decEdit.text().toInt();
            double dia = diaEdit.text().toDouble();
            if (!service.addStar(name, astronomer.constellation, ra, dec, dia)) {
                QMessageBox::warning(&dlg, "Error", "Invalid data or duplicate name.");
                return;
            }
            dlg.accept();
        });
        connect(&cancel, &QPushButton::clicked, [&]() { dlg.reject(); });

        dlg.exec();
    });

    connect(updateBtn, &QPushButton::clicked, [=]() {
        auto idx = table->currentIndex();
        if (!idx.isValid()) return;
        Star s = model->getStarAt(idx.row());

        QDialog dlg(this);
        dlg.setWindowTitle("Update Star");
        QFormLayout form(&dlg);

        QLineEdit nameEdit(QString::fromStdString(s.name));
        QLineEdit raEdit(QString::number(s.ra));
        QLineEdit decEdit(QString::number(s.dec));
        QLineEdit diaEdit(QString::number(s.diameter));
        form.addRow("Name:", &nameEdit);
        form.addRow("RA:", &raEdit);
        form.addRow("Dec:", &decEdit);
        form.addRow("Diameter:", &diaEdit);

        QPushButton ok("Update"), cancel("Cancel");
        QHBoxLayout btns;
        btns.addWidget(&ok); btns.addWidget(&cancel);
        form.addRow(&btns);

        connect(&ok, &QPushButton::clicked, [&]() {
            std::string newName = nameEdit.text().toStdString();
            int ra = raEdit.text().toInt();
            int dec = decEdit.text().toInt();
            double dia = diaEdit.text().toDouble();
            if (!service.updateStar(s.name, newName, ra, dec, dia)) {
                QMessageBox::warning(&dlg, "Error", "Invalid data (name empty or diameter <= 10).");
                return;
            }
            dlg.accept();
        });
        connect(&cancel, &QPushButton::clicked, [&]() { dlg.reject(); });

        dlg.exec();
    });

    connect(viewBtn, &QPushButton::clicked, [=]() {
        auto idx = table->currentIndex();
        if (!idx.isValid()) return;
        Star s = model->getStarAt(idx.row());
        auto stars = service.getStarsByConstellation(astronomer.constellation);

        QDialog dlg(this);
        dlg.setWindowTitle("Constellation View");
        QVBoxLayout lay(&dlg);
        ConstellationView* view = new ConstellationView(stars, s, &dlg);
        view->setMinimumSize(300, 300);
        lay.addWidget(view);
        dlg.exec();
        });

    connect(searchEdit, &QLineEdit::textChanged, [=](const QString& text) {
        searchList->clear();
        for (const auto& s : service.searchStars(text.toStdString()))
            searchList->addItem(QString::fromStdString(s.name));
    });
}