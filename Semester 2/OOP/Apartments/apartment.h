#pragma once
#include <string>

class Apartment {
private:
    int surface;
    std::string street;
    int price;

public:
    Apartment(int surface, const std::string& street, int price)
        : surface(surface), street(street), price(price) {
    }

    int getSurface() const { return surface; }
    std::string getStreet() const { return street; }
    int getPrice() const { return price; }

    std::string toString() const {
        return street + " (" + std::to_string(surface) + "m^2) " + std::to_string(price) + " euro";
    }
};
