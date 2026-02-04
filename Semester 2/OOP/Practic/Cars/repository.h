#pragma once
#include <vector>
#include "cars.h"
#include <fstream>
#include <sstream>

class Repository
{
private:
    std::vector<Car> carsList;

public:
    Repository() { this->loadRepo(); }
    void loadRepo();
    std::vector<Car> getCars() const { return this->carsList; }
};