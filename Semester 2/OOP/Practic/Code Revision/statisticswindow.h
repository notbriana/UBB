#pragma once
#include <QWidget>
#include <vector>
#include "domain.h"

class StatisticsWindow : public QWidget {
    Q_OBJECT
    std::vector<Programmer> programmers;
public:
    StatisticsWindow(const std::vector<Programmer>& programmers, QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
};