#pragma once
#include <string>
#include <vector>

class Courier {
private:
    std::string name;
    std::vector<std::string> streets;
    double centerX, centerY, radius;

public:
    Courier(const std::string& name, const std::vector<std::string>& streets,
        double cx, double cy, double r);

    std::string getName() const;
    std::vector<std::string> getStreets() const;
    bool isInZone(double x, double y) const;
    double getCenterX() const { return centerX; }
    double getCenterY() const { return centerY; }
    double getRadius() const { return radius; }
};

class Package {
private:
    std::string recipient;
    std::string address;
    double x, y;
    bool delivered;

public:
    Package(const std::string& recipient, const std::string& address,
        double x, double y, bool delivered);

    std::string getStreet() const;
    std::string getRecipient() const;
    std::string getAddress() const;
    double getX() const;
    double getY() const;
    bool isDelivered() const;
    void setDelivered(bool value) {
        delivered = value;
    }
    inline bool operator==(const Package& other) const {
        return recipient == other.recipient &&
               address == other.address &&
               x == other.x &&
               y == other.y;
    }
    void deliver();
};
