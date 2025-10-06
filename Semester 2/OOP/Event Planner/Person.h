#pragma once
#include <string>
#include "Event.h"

class Person {
    std::string name;
    Location location;
    bool isOrganiser;
public:
    Person(const std::string& name, const Location& location, bool isOrganiser);

    const std::string& getName() const;
    const Location& getLocation() const;
    bool getIsOrganiser() const;
};