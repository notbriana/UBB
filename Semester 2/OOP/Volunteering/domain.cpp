#include "domain.h"
#include <sstream>

Department::Department(const std::string& n, const std::string& d) : name(n), description(d) {}
const std::string& Department::getName() const { return name; }
const std::string& Department::getDescription() const { return description; }

Volunteer::Volunteer(const std::string& n, const std::string& e, const std::vector<std::string>& i, const std::string& d)
    : name(n), email(e), interests(i), department(d) {}
const std::string& Volunteer::getName() const { return name; }
const std::string& Volunteer::getEmail() const { return email; }
const std::vector<std::string>& Volunteer::getInterests() const { return interests; }
const std::string& Volunteer::getDepartment() const { return department; }
void Volunteer::setDepartment(const std::string& d) { department = d; }