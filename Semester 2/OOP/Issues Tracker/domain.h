#pragma once
#include <string>

class User {
public:
    std::string name;
    std::string type; // "tester" or "programmer"
    User(const std::string& n, const std::string& t) : name(n), type(t) {}
};

class Issue {
public:
    std::string description;
    std::string status; // "open" or "closed"
    std::string reporter;
    std::string solver;
    Issue(const std::string& d, const std::string& s, const std::string& r, const std::string& so)
        : description(d), status(s), reporter(r), solver(so) {}
};