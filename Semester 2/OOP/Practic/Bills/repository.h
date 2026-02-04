#pragma once
#include <vector>
#include "bills.h"
#include <fstream>
#include <sstream>

class repository
{
private:
    std::vector<bills> billsList;

public:
    repository() { this->loadRepo(); }
    void loadRepo();
    std::vector<bills> getBills() const { return this->billsList; }
};