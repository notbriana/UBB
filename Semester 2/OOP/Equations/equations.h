#pragma once
#include <string>
#include <complex>
#include <vector>
#include <sstream>
#include <iomanip>

class Equation
{
private:
    double a, b, c;

public:
    Equation(double a, double b, double c) : a(a), b(b), c(c) {}

    // Getters
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }

    // Check if equation has real solutions
    bool hasRealSolutions() const {
        double discriminant = b * b - 4 * a * c;
        return discriminant >= 0;
    }

    // Get discriminant
    double getDiscriminant() const {
        return b * b - 4 * a * c;
    }

    // Get solutions as complex numbers (handles both real and imaginary)
    std::pair<std::complex<double>, std::complex<double>> getSolutions() const {
        if (a == 0) {
            // Linear equation: bx + c = 0
            if (b == 0) {
                // No solution or infinite solutions
                return { std::complex<double>(0, 0), std::complex<double>(0, 0) };
            }
            double solution = -c / b;
            return { std::complex<double>(solution, 0), std::complex<double>(solution, 0) };
        }

        double discriminant = getDiscriminant();
        std::complex<double> sqrtDiscriminant;

        if (discriminant >= 0) {
            sqrtDiscriminant = std::complex<double>(sqrt(discriminant), 0);
        }
        else {
            sqrtDiscriminant = std::complex<double>(0, sqrt(-discriminant));
        }

        std::complex<double> solution1 = (-b + sqrtDiscriminant) / (2.0 * a);
        std::complex<double> solution2 = (-b - sqrtDiscriminant) / (2.0 * a);

        return { solution1, solution2 };
    }

    // Convert to mathematical form string
    std::string toMathematicalForm() const {
        std::ostringstream oss;

        // Handle coefficient a
        if (a == 1) {
            oss << "x^2";
        }
        else if (a == -1) {
            oss << "-x^2";
        }
        else if (a != 0) {
            oss << a << "*x^2";
        }

        // Handle coefficient b
        if (b != 0) {
            if (a != 0) { // Not the first term
                if (b > 0) oss << " + ";
                else oss << " - ";

                double absB = abs(b);
                if (absB == 1) {
                    oss << "x";
                }
                else {
                    oss << absB << "*x";
                }
            }
            else { // First term
                if (b == 1) {
                    oss << "x";
                }
                else if (b == -1) {
                    oss << "-x";
                }
                else {
                    oss << b << "*x";
                }
            }
        }

        // Handle coefficient c
        if (c != 0) {
            if (a != 0 || b != 0) { // Not the first term
                if (c > 0) oss << " + " << c;
                else oss << " - " << abs(c);
            }
            else { // First term
                oss << c;
            }
        }

        // Handle special case where all coefficients result in empty string
        std::string result = oss.str();
        if (result.empty()) {
            result = "0";
        }

        return result;
    }

    // Convert to string for file storage
    std::string toString() const {
        std::ostringstream oss;
        oss << a << ", " << b << ", " << c;
        return oss.str();
    }
};