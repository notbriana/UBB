#pragma once
#include "repository.h"
#include <string>
#include <sstream>
#include <iomanip>

class EquationService
{
private:
    EquationRepository repository;

public:
    EquationService() : repository("equations.txt") {}

    std::vector<Equation> getAllEquations() {
        return repository.getAllEquations();
    }

    void addEquation(double a, double b, double c) {
        Equation newEquation(a, b, c);
        repository.addEquation(newEquation);
    }

    std::string getSolutionsString(const Equation& equation) {
        auto solutions = equation.getSolutions();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3);

        if (equation.getA() == 0) {
            if (equation.getB() == 0) {
                if (equation.getC() == 0) {
                    oss << "Infinite solutions (0 = 0)";
                }
                else {
                    oss << "No solution (" << equation.getC() << " = 0)";
                }
            }
            else {
                oss << "Linear equation: x = " << solutions.first.real();
            }
        }
        else {
            double discriminant = equation.getDiscriminant();

            if (discriminant > 0) {
                oss << "Two real solutions:\n";
                oss << "x1 = " << solutions.first.real() << "\n";
                oss << "x2 = " << solutions.second.real();
            }
            else if (discriminant == 0) {
                oss << "One real solution (repeated):\n";
                oss << "x = " << solutions.first.real();
            }
            else {
                oss << "Two complex solutions:\n";
                oss << "x1 = " << solutions.first.real();
                if (solutions.first.imag() >= 0) {
                    oss << " + " << solutions.first.imag() << "i\n";
                }
                else {
                    oss << " - " << abs(solutions.first.imag()) << "i\n";
                }
                oss << "x2 = " << solutions.second.real();
                if (solutions.second.imag() >= 0) {
                    oss << " + " << solutions.second.imag() << "i";
                }
                else {
                    oss << " - " << abs(solutions.second.imag()) << "i";
                }
            }
        }

        return oss.str();
    }

    void refreshData() {
        repository.loadFromFile();
    }
};