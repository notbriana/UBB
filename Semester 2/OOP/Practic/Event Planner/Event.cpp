#include "Event.h"

Event::Event(const std::string& organiser, const std::string& name, const std::string& description,
             const Location& location, const std::string& date)
    : organiser(organiser), name(name), description(description), location(location), date(date) {}

const std::string& Event::getOrganiser() const { return organiser; }
const std::string& Event::getName() const { return name; }
const std::string& Event::getDescription() const { return description; }
const Location& Event::getLocation() const { return location; }
const std::string& Event::getDate() const { return date; }
const std::set<std::string>& Event::getAttendees() const { return attendees; }

void Event::setDescription(const std::string& desc) { description = desc; }
void Event::setDate(const std::string& d) { date = d; }
void Event::addAttendee(const std::string& personName) { attendees.insert(personName); }
bool Event::isAttending(const std::string& personName) const { return attendees.count(personName) > 0; }

bool Event::operator==(const Event& other) const {
    return name == other.name &&
           location.latitude == other.location.latitude &&
           location.longitude == other.location.longitude;
}