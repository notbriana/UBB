#include "service.h"
#include <algorithm>

std::vector<Car> Service::getCarsSorted() const
{
    std::vector<Car> allCars = this->repo.getCars();
    std::sort(allCars.begin(), allCars.end());
    return allCars;
}

std::vector<Car> Service::getCarsByManufacturer(const std::string& manufacturer) const
{
    std::vector<Car> allCars = this->repo.getCars();
    std::vector<Car> filteredCars;

    for (const auto& car : allCars) {
        if (car.getManufacturer() == manufacturer) {
            filteredCars.push_back(car);
        }
    }

    std::sort(filteredCars.begin(), filteredCars.end(),
        [](const Car& a, const Car& b) {
            return a.getModel() < b.getModel();
        });

    return filteredCars;
}

int Service::getNumberOfCarsByManufacturer(const std::string& manufacturer) const
{
    if (manufacturer.empty()) {
        return 0;
    }

    std::vector<Car> allCars = this->repo.getCars();
    int count = 0;

    for (const auto& car : allCars) {
        if (car.getManufacturer() == manufacturer) {
            count++;
        }
    }

    return count;
}

bool Service::manufacturerExists(const std::string& manufacturer) const
{
    std::vector<Car> allCars = this->repo.getCars();

    for (const auto& car : allCars) {
        if (car.getManufacturer() == manufacturer) {
            return true;
        }
    }

    return false;
}