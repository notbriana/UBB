#pragma once
#include <string>

class Astronomer {
public:
    std::string name;
    std::string constellation;
    Astronomer(const std::string& n, const std::string& c) : name(n), constellation(c) {}
};

class Star {
public:
    std::string name;
    std::string constellation;
    int ra, dec;
    double diameter;
    Star(const std::string& n, const std::string& c, int r, int d, double dia)
        : name(n), constellation(c), ra(r), dec(d), diameter(dia) {}
};