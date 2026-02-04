#include "service.h"

std::vector<Apartment> Service::filterBySurface(int min, int max) {
    std::vector<Apartment> result;
    for (const auto& apt : repo.getAll()) {
        if (apt.getSurface() >= min && apt.getSurface() <= max) {
            result.push_back(apt);
        }
    }
    return result;
}

std::vector<Apartment> Service::filterByPrice(int min, int max, int minSurface, int maxSurface) {
    std::vector<Apartment> result;
    for (const auto& apt : repo.getAll()) {
        if (apt.getPrice() >= min && apt.getPrice() <= max) {
            if ((minSurface == -1 || apt.getSurface() >= minSurface) &&
                (maxSurface == -1 || apt.getSurface() <= maxSurface)) {
                result.push_back(apt);
            }
        }
    }
    return result;
}
