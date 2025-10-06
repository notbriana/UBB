#include "domain.h"
#include <cmath>
#include <sstream>

Courier::Courier(const std::string& name, const std::vector<std::string>& streets,
    double cx, double cy, double r)
    : name(name), streets(streets), centerX(cx), centerY(cy), radius(r) {
}

std::string Courier::getName() const { return name; }

std::vector<std::string> Courier::getStreets() const { return streets; }

bool Courier::isInZone(double x, double y) const {
    return (centerX - x) * (centerX - x) + (centerY - y) * (centerY - y) <= radius * radius;
}

Package::Package(const std::string& recipient, const std::string& address,
    double x, double y, bool delivered)
    : recipient(recipient), address(address), x(x), y(y), delivered(delivered) {
}

std::string Package::getStreet() const {
    // Extract street name (before the first digit or before the first space+digit)
    std::string street = address;
    auto pos = street.find_first_of("0123456789");
    if (pos != std::string::npos) {
        // Remove trailing space if present
        while (pos > 0 && street[pos - 1] == ' ') --pos;
        street = street.substr(0, pos);
    }
    // Trim trailing spaces
    while (!street.empty() && street.back() == ' ') street.pop_back();
    return street;
}

std::string Package::getRecipient() const { return recipient; }
std::string Package::getAddress() const { return address; }
double Package::getX() const { return x; }
double Package::getY() const { return y; }
bool Package::isDelivered() const { return delivered; }

void Package::deliver() { delivered = true; }
