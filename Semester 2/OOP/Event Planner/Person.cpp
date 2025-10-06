#include "Person.h"

Person::Person(const std::string& name, const Location& location, bool isOrganiser)
    : name(name), location(location), isOrganiser(isOrganiser) {}

const std::string& Person::getName() const { return name; }
const Location& Person::getLocation() const { return location; }
bool Person::getIsOrganiser() const { return isOrganiser; }