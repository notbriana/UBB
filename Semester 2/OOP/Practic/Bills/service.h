#pragma once
#include "repository.h"
#include <vector>
#include <string>

class Service
{
private:
    repository repo;

public:
    Service() {}

    std::vector<bills> getBills() const { return repo.getBills(); }
    std::vector<bills> getBillsSorted() const;
    std::vector<bills> getUnpaidBills() const;
    std::vector<bills> getPaidBills() const;
    double calculateAmountOfBillsFromCompany(std::string company);
    bool companyExists(std::string company) const;
};