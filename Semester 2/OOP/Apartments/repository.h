#pragma once
#include <vector>
#include "apartment.h"

class Repository {
private:
    std::vector<Apartment> apartments;

public:
    Repository();
    void loadFromFile();
    void deleteApartment(int index);
    const std::vector<Apartment>& getAll() const { return apartments; }
};
