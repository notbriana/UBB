#include "repository.h"
#include <iostream>
#include <algorithm>

void Repository::loadRepo()
{
    std::ifstream file("cars.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open cars.txt file!" << std::endl;
        return;
    }

    std::string line, manufacturer, model, yearString, color;
    int year;
    const char delimiter = '|';

    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        std::istringstream iss(line);

        if (getline(iss, manufacturer, delimiter) &&
            getline(iss, model, delimiter) &&
            getline(iss, yearString, delimiter) &&
            getline(iss, color, delimiter)) {

            // Trim whitespace
            manufacturer.erase(0, manufacturer.find_first_not_of(" \t"));
            manufacturer.erase(manufacturer.find_last_not_of(" \t") + 1);

            model.erase(0, model.find_first_not_of(" \t"));
            model.erase(model.find_last_not_of(" \t") + 1);

            yearString.erase(0, yearString.find_first_not_of(" \t"));
            yearString.erase(yearString.find_last_not_of(" \t") + 1);

            color.erase(0, color.find_first_not_of(" \t"));
            color.erase(color.find_last_not_of(" \t") + 1);

            try {
                year = std::stoi(yearString);

                this->carsList.push_back(Car(manufacturer, model, year, color));
                std::cout << "Loaded: " << this->carsList.back().toString()
                    << " - Color: " << color << std::endl;
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
    std::cout << "Total cars loaded: " << this->carsList.size() << std::endl;
}