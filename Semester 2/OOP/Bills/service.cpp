#include "service.h"
#include <algorithm>

std::vector<bills> Service::getBillsSorted() const
{
    std::vector<bills> allBills = this->repo.getBills();
    std::sort(allBills.begin(), allBills.end());
    return allBills;
}

std::vector<bills> Service::getUnpaidBills() const
{
    std::vector<bills> allBills = this->repo.getBills();
    std::vector<bills> unpaidBills;

    for (const auto& bill : allBills) {
        if (!bill.getIsPaid()) {
            unpaidBills.push_back(bill);
        }
    }

    std::sort(unpaidBills.begin(), unpaidBills.end());
    return unpaidBills;
}

std::vector<bills> Service::getPaidBills() const
{
    std::vector<bills> allBills = this->repo.getBills();
    std::vector<bills> paidBills;

    for (const auto& bill : allBills) {
        if (bill.getIsPaid()) {
            paidBills.push_back(bill);
        }
    }

    std::sort(paidBills.begin(), paidBills.end());
    return paidBills;
}

double Service::calculateAmountOfBillsFromCompany(std::string company)
{
    std::vector<bills> allBills = this->repo.getBills();
    double amount = 0;

    for (const auto& bill : allBills) {
        if (bill.getCompanyName() == company && !bill.getIsPaid()) {
            amount += bill.getSum();
        }
    }

    return amount;
}

bool Service::companyExists(std::string company) const
{
    std::vector<bills> allBills = this->repo.getBills();

    for (const auto& bill : allBills) {
        if (bill.getCompanyName() == company) {
            return true;
        }
    }

    return false;
}