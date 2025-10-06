#include "mapwidget.h"

MapWidget::MapWidget(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {}

void MapWidget::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Draw packages
    for (const auto& pkg : service.getAllPackages()) {
        if (pkg.isDelivered())
            p.setBrush(Qt::green);
        else
            p.setBrush(Qt::red);

        int px = static_cast<int>(pkg.getX()) * 10;
        int py = static_cast<int>(pkg.getY()) * 10;
        p.drawEllipse(px, py, 10, 10);
    }

    // Draw courier zones
    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::blue);
    for (const auto& c : service.getCouriers()) {
        int cx = static_cast<int>(c.isInZone(0, 0) ? c.isInZone(0, 0) : c.getStreets().size()) * 10;
        int cy = static_cast<int>(c.getStreets().size()) * 10;
        int radius = static_cast<int>(50); // demo radius
        p.drawEllipse(cx - radius, cy - radius, radius * 2, radius * 2);
    }
}