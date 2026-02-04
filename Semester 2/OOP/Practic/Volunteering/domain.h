#pragma once
#include <string>
#include <vector>

class Department {
    std::string name;
    std::string description;
public:
    Department(const std::string& n, const std::string& d);
    const std::string& getName() const;
    const std::string& getDescription() const;
};

class Volunteer {
    std::string name;
    std::string email;
    std::vector<std::string> interests;
    std::string department; // empty if unassigned
public:
    Volunteer(const std::string& n, const std::string& e, const std::vector<std::string>& i, const std::string& d = "");
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::vector<std::string>& getInterests() const;
    const std::string& getDepartment() const;
    void setDepartment(const std::string& d);
};