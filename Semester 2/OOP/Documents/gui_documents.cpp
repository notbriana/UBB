#include "gui_documents.h"

gui_documents::gui_documents(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(searchLine);
    layout->addWidget(documentList);
    layout->addWidget(bestMatchButton);
    setLayout(layout);

    populateList();

    connect(searchLine, &QLineEdit::textChanged, this, &gui_documents::filterList);
    connect(bestMatchButton, &QPushButton::clicked, this, &gui_documents::showBestMatch);
}

void gui_documents::populateList() {
    documentList->clear();
    for (const auto& doc : service.getAllDocumentsSorted()) {
        documentList->addItem(QString::fromStdString(doc.toStdString()));
    }
}

void gui_documents::filterList(const QString& text) {
    documentList->clear();
    for (const auto& doc : service.searchDocuments(text.toStdString())) {
        documentList->addItem(QString::fromStdString(doc.toStdString()));
    }
}

void gui_documents::showBestMatch() {
    std::string query = searchLine->text().toStdString();
    Document best = service.getBestMatch(query);
    QMessageBox::information(this, "Best Match", QString::fromStdString(best.getName() + "\n" + best.getKeywords() + "\n" + best.getContent()));
}
