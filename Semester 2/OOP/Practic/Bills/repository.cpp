#include "repository.h"
#include <iostream>

void repository::loadRepo()
{
    std::ifstream file("bills.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open bills.txt file!" << std::endl;
        return;
    }

    std::string line, companyName, code, sumString, isPaidString;
    double sum;
    bool isPaid;
    const char delimiter = '|';

    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        std::istringstream iss(line);

        if (getline(iss, companyName, delimiter) &&
            getline(iss, code, delimiter) &&
            getline(iss, sumString, delimiter) &&
            getline(iss, isPaidString, delimiter)) {

            try {
                sum = std::stod(sumString);
                isPaid = (isPaidString == "true");

                this->billsList.push_back(bills(companyName, code, sum, isPaid));
                std::cout << "Loaded: " << this->billsList.back().toString() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Error parsing line format: " << line << std::endl;
        }
    }

    file.close();
    std::cout << "Total bills loaded: " << this->billsList.size() << std::endl;
}