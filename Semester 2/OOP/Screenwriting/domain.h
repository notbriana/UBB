#pragma once
#include <string>

class Writer {
    std::string name;
    std::string expertise; // Assistant, Junior, Senior
public:
    Writer(const std::string& n, const std::string& e) : name(n), expertise(e) {}
    const std::string& getName() const { return name; }
    const std::string& getExpertise() const { return expertise; }
};

class Idea {
    std::string description;
    std::string status; // proposed, accepted
    std::string creator;
    int act; // 1, 2, 3
    std::string development; // for developed text
public:
    Idea(const std::string& d, const std::string& s, const std::string& c, int a)
        : description(d), status(s), creator(c), act(a) {}
    const std::string& getDescription() const { return description; }
    const std::string& getStatus() const { return status; }
    const std::string& getCreator() const { return creator; }
    int getAct() const { return act; }
    const std::string& getDevelopment() const { return development; }
    void setStatus(const std::string& s) { status = s; }
    void setDevelopment(const std::string& dev) { development = dev; }
};