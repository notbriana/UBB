#include "repository.h"
#include <fstream>
#include <sstream>

Repository::Repository() {
    loadFromFile();
}

void Repository::loadFromFile() {
    std::ifstream fin("apartments.txt");
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream ss(line);
        int surface, price;
        std::string street;
        char delim;

        ss >> surface >> delim;
        std::getline(ss, street, '|');
        ss >> price;

        apartments.emplace_back(surface, street, price);
    }
}

void Repository::deleteApartment(int index) {
    if (index >= 0 && index < apartments.size()) {
        apartments.erase(apartments.begin() + index);
    }
}
