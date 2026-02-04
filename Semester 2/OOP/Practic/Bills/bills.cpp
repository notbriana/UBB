#include "bills.h"
#include <sstream>
#include <iomanip>

bills::bills() : companyName(""), code(""), sum(0.0), isPaid(false)
{
}

bills::bills(std::string companyName, std::string code, double sum, bool isPaid)
    : companyName(companyName), code(code), sum(sum), isPaid(isPaid)
{
}

std::string bills::toString() const
{
    std::stringstream ss;
    ss << companyName << " - $" << std::fixed << std::setprecision(2) << sum
        << " (" << (isPaid ? "Paid" : "Unpaid") << ")";
    return ss.str();
}