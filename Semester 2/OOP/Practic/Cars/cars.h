#pragma once

#include <string>
#include <QColor>

class Car
{
private:
    std::string manufacturer;
    std::string model;
    int year;
    std::string color;

public:
    // Constructors
    Car();
    Car(std::string manufacturer, std::string model, int year, std::string color);

    // Getters
    std::string getManufacturer() const { return manufacturer; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    std::string getColor() const { return color; }

    // Setters
    void setManufacturer(const std::string& m) { manufacturer = m; }
    void setModel(const std::string& m) { model = m; }
    void setYear(int y) { year = y; }
    void setColor(const std::string& c) { color = c; }

    // Utility methods
    std::string toString() const;
    QColor getQColor() const;

    // Comparison operator for sorting by manufacturer
    bool operator<(const Car& other) const {
        if (manufacturer == other.manufacturer) {
            return model < other.model; // Secondary sort by model
        }
        return manufacturer < other.manufacturer;
    }

    bool operator==(const Car& other) const {
        return manufacturer == other.manufacturer &&
            model == other.model &&
            year == other.year &&
            color == other.color;
    }
};