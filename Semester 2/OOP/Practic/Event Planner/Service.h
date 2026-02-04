#pragma once
#include <vector>
#include <string>
#include "Event.h"
#include "Person.h"
#include "FileRepo.h"

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Service {
    std::vector<Event> events;
    std::vector<Person> people;
    FileRepo& repo;
    std::vector<Observer*> observers;
public:
    Service(FileRepo& repo);

    void load();
    void save();

    const std::vector<Event>& getEvents() const;
    const std::vector<Person>& getPeople() const;

    std::vector<Event> getEventsSortedByDate() const;
    std::vector<Event> getEventsNear(const Person& person, double maxDist) const;
    void addEvent(const Event& event);
    void attendEvent(const std::string& personName, const std::string& eventName);
    void updateEvent(const std::string& eventName, const std::string& newDesc, const std::string& newDate);

    std::vector<Event> getPopularEvents() const;

    void addObserver(Observer* obs);
    void notifyObservers();
};