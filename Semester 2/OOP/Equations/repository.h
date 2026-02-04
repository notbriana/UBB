#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "equations.h"

class EquationRepository
{
private:
    std::vector<Equation> equations;
    std::string filename;

public:
    EquationRepository(const std::string& filename = "equations.txt") : filename(filename) {
        loadFromFile();
    }

    void loadFromFile() {
        equations.clear();
        std::ifstream file(filename);
        std::string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string aStr, bStr, cStr;

            // Parse comma-separated values
            if (getline(iss, aStr, ',') &&
                getline(iss, bStr, ',') &&
                getline(iss, cStr)) {

                try {
                    double a = std::stod(aStr);
                    double b = std::stod(bStr);
                    double c = std::stod(cStr);
                    equations.push_back(Equation(a, b, c));
                }
                catch (const std::exception&) {
                    // Skip invalid lines
                    continue;
                }
            }
        }
        file.close();
    }

    void saveToFile() {
        std::ofstream file(filename);
        for (const auto& eq : equations) {
            file << eq.toString() << std::endl;
        }
        file.close();
    }

    std::vector<Equation> getAllEquations() const {
        return equations;
    }

    void addEquation(const Equation& equation) {
        equations.push_back(equation);
        saveToFile();
    }

    size_t getEquationCount() const {
        return equations.size();
    }
};