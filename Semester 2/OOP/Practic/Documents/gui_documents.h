#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include "service.h"



class gui_documents : public QWidget {
    Q_OBJECT

private:
    Service service;
    QListWidget* documentList = new QListWidget();
    QLineEdit* searchLine = new QLineEdit();
    QPushButton* bestMatchButton = new QPushButton("Show Best Match");

public:
    gui_documents(QWidget* parent = nullptr);

private slots:
    void populateList();
    void filterList(const QString& text);
    void showBestMatch();
};


