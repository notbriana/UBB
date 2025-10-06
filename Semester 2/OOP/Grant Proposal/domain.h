#pragma once
#include <string>

class Researcher {
public:
    std::string name;
    std::string position; // "phd student", "postdoc", "senior"
    Researcher(const std::string& n, const std::string& p) : name(n), position(p) {}
};

class Idea {
public:
    std::string title;
    std::string description;
    std::string status; // "proposed" or "accepted"
    std::string creator;
    int duration; // 1, 2, or 3

    Idea(const std::string& t, const std::string& d, const std::string& s, const std::string& c, int dur)
        : title(t), description(d), status(s), creator(c), duration(dur) {}
};