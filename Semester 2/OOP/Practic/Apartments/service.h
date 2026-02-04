#pragma once
#include "repository.h"

class Service {
private:
    Repository& repo;

public:
    Service(Repository& r) : repo(r) {}

    std::vector<Apartment> getAll() const { return repo.getAll(); }
    void deleteApartment(int index) { repo.deleteApartment(index); }

    std::vector<Apartment> filterBySurface(int min, int max);
    std::vector<Apartment> filterByPrice(int min, int max, int minSurface = -1, int maxSurface = -1);
};
