#pragma once
#include <QWidget>
#include <QPainter>
#include "service.h"

class MapWidget : public QWidget {
    Q_OBJECT

private:
    Service& service;

protected:
    void paintEvent(QPaintEvent* event) override;

public:
    explicit MapWidget(Service& service, QWidget* parent = nullptr);
};