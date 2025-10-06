#include "Service.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

Service::Service(FileRepo& repo) : repo(repo) {}

void Service::load() {
    events = repo.loadEvents();
    people = repo.loadPeople();
}

void Service::save() {
    repo.saveEvents(events);
}

const std::vector<Event>& Service::getEvents() const { return events; }
const std::vector<Person>& Service::getPeople() const { return people; }

std::vector<Event> Service::getEventsSortedByDate() const {
    auto sorted = events;
    std::sort(sorted.begin(), sorted.end(), [](const Event& a, const Event& b) {
        return a.getDate() < b.getDate();
    });
    return sorted;
}

double euclidean(const Location& a, const Location& b) {
    return std::sqrt((a.latitude - b.latitude) * (a.latitude - b.latitude) +
                     (a.longitude - b.longitude) * (a.longitude - b.longitude));
}

std::vector<Event> Service::getEventsNear(const Person& person, double maxDist) const {
    std::vector<Event> result;
    for (const auto& ev : events) {
        if (euclidean(person.getLocation(), ev.getLocation()) <= maxDist)
            result.push_back(ev);
    }
    return result;
}

void Service::addEvent(const Event& event) {
    for (const auto& ev : events)
        if (ev == event)
            throw std::runtime_error("Duplicate event name and location");
    events.push_back(event);
    notifyObservers();
}

void Service::attendEvent(const std::string& personName, const std::string& eventName) {
    for (auto& ev : events) {
        if (ev.getName() == eventName) {
            if (!ev.isAttending(personName)) {
                ev.addAttendee(personName);
                notifyObservers();
            }
            return;
        }
    }
}

void Service::updateEvent(const std::string& eventName, const std::string& newDesc, const std::string& newDate) {
    for (auto& ev : events) {
        if (ev.getName() == eventName) {
            ev.setDescription(newDesc);
            ev.setDate(newDate);
            notifyObservers();
            return;
        }
    }
}

std::vector<Event> Service::getPopularEvents() const {
    auto sorted = events;
    std::sort(sorted.begin(), sorted.end(), [](const Event& a, const Event& b) {
        return a.getAttendees().size() > b.getAttendees().size();
    });
    return sorted;
}

void Service::addObserver(Observer* obs) { observers.push_back(obs); }
void Service::notifyObservers() { for (auto obs : observers) obs->update(); }