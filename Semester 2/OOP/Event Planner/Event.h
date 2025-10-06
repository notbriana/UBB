#pragma once
#include <string>
#include <vector>
#include <set>

struct Location {
    double latitude;
    double longitude;
};

class Event {
    std::string organiser;
    std::string name;
    std::string description;
    Location location;
    std::string date;
    std::set<std::string> attendees;
public:
    Event(const std::string& organiser, const std::string& name, const std::string& description,
          const Location& location, const std::string& date);

    const std::string& getOrganiser() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const Location& getLocation() const;
    const std::string& getDate() const;
    const std::set<std::string>& getAttendees() const;

    void setDescription(const std::string& desc);
    void setDate(const std::string& date);
    void addAttendee(const std::string& personName);
    bool isAttending(const std::string& personName) const;
    bool operator==(const Event& other) const;
};