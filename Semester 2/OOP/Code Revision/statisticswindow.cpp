#include "statisticswindow.h"
#include <QPainter>
#include <QFontMetrics>

StatisticsWindow::StatisticsWindow(const std::vector<Programmer>& programmers, QWidget* parent)
    : QWidget(nullptr), programmers(programmers) { // Use nullptr for top-level window
    setWindowTitle("Programmer Statistics");
    resize(400, 80 + 60 * programmers.size());
    setWindowFlags(Qt::Window); // Make it a top-level window
    setAttribute(Qt::WA_NoSystemBackground, false);
    setAttribute(Qt::WA_TranslucentBackground, false);
}

void StatisticsWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    int y = 40;
    int maxRadius = 40;
    int minRadius = 10;

    for (const auto& p : programmers) {
        // Proportional radius to the programmer's own progress
        int radius = minRadius;
        if (p.total_files_to_revise > 0) {
            double percent = static_cast<double>(p.revised_files) / p.total_files_to_revise;
            radius = minRadius + static_cast<int>(percent * (maxRadius - minRadius));
        }

        // Blue for completed, black otherwise
        QColor color = (p.revised_files == p.total_files_to_revise) ? Qt::blue : Qt::black;
        painter.setPen(color);
        painter.setBrush(QBrush(color, Qt::SolidPattern));

        painter.drawEllipse(30, y - radius / 2, radius, radius);

        painter.setPen(color);
        QFont font = painter.font();
        font.setBold(p.revised_files == p.total_files_to_revise);
        painter.setFont(font);

        painter.drawText(50 + maxRadius, y + 5, QString::fromStdString(p.name) + QString(" (%1/%2)").arg(p.revised_files).arg(p.total_files_to_revise));
        y += 60;
    }
}