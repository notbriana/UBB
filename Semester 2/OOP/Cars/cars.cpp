#include "cars.h"
#include <sstream>

Car::Car() : manufacturer(""), model(""), year(0), color("")
{
}

Car::Car(std::string manufacturer, std::string model, int year, std::string color)
    : manufacturer(manufacturer), model(model), year(year), color(color)
{
}

std::string Car::toString() const
{
    std::stringstream ss;
    ss << manufacturer << " " << model << " (" << year << ")";
    return ss.str();
}

QColor Car::getQColor() const
{
    // Convert string color to Qt color
    std::string lowerColor = color;
    std::transform(lowerColor.begin(), lowerColor.end(), lowerColor.begin(), ::tolower);

    if (lowerColor == "red") return QColor(Qt::red);
    else if (lowerColor == "blue") return QColor(Qt::blue);
    else if (lowerColor == "green") return QColor(Qt::green);
    else if (lowerColor == "yellow") return QColor(Qt::yellow);
    else if (lowerColor == "black") return QColor(Qt::black);
    else if (lowerColor == "white") return QColor(Qt::white);
    else if (lowerColor == "gray" || lowerColor == "grey") return QColor(Qt::gray);
    else if (lowerColor == "cyan") return QColor(Qt::cyan);
    else if (lowerColor == "magenta") return QColor(Qt::magenta);
    else if (lowerColor == "darkred") return QColor(Qt::darkRed);
    else if (lowerColor == "darkblue") return QColor(Qt::darkBlue);
    else if (lowerColor == "darkgreen") return QColor(Qt::darkGreen);
    else if (lowerColor == "orange") return QColor(255, 165, 0); // Orange
    else if (lowerColor == "purple") return QColor(128, 0, 128); // Purple
    else if (lowerColor == "brown") return QColor(165, 42, 42); // Brown
    else if (lowerColor == "pink") return QColor(255, 192, 203); // Pink
    else return QColor(Qt::black); // Default color
}