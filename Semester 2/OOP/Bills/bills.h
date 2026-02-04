#pragma once

#include <string>

class bills
{
private:
    std::string companyName;
    std::string code;
    double sum;
    bool isPaid;

public:
    // Constructors
    bills();
    bills(std::string companyName, std::string code, double sum, bool isPaid);

    // Getters
    std::string getCompanyName() const { return companyName; }
    std::string getCode() const { return code; }
    double getSum() const { return sum; }
    bool getIsPaid() const { return isPaid; }

    // Setters
    void setCompanyName(const std::string& name) { companyName = name; }
    void setCode(const std::string& c) { code = c; }
    void setSum(double s) { sum = s; }
    void setIsPaid(bool paid) { isPaid = paid; }

    // Utility methods
    std::string toString() const;

    // Comparison operator for sorting by company name
    bool operator<(const bills& other) const {
        return companyName < other.companyName;
    }

    bool operator==(const bills& other) const {
        return companyName == other.companyName &&
            code == other.code &&
            sum == other.sum &&
            isPaid == other.isPaid;
    }
};