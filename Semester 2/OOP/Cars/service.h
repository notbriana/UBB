#pragma once
#include "repository.h"
#include <vector>
#include <string>

class Service
{
private:
    Repository repo;

public:
    Service() {}

    std::vector<Car> getCars() const { return repo.getCars(); }
    std::vector<Car> getCarsSorted() const;
    std::vector<Car> getCarsByManufacturer(const std::string& manufacturer) const;

    /**
     * Computes the number of cars for a given manufacturer.
     *
     * @param manufacturer The name of the manufacturer (case-sensitive)
     * @return The number of cars from the specified manufacturer
     *
     * Specification:
     * - Input: A string representing the manufacturer name
     * - Output: An integer representing the count of cars
     * - Preconditions: manufacturer parameter should not be null/empty for meaningful results
     * - Postconditions: Returns 0 if no cars found, positive integer otherwise
     * - Side effects: None (read-only operation)
     * - Exception handling: Does not throw exceptions, returns 0 for invalid input
     */
    int getNumberOfCarsByManufacturer(const std::string& manufacturer) const;

    bool manufacturerExists(const std::string& manufacturer) const;
};