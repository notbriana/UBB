#pragma once
#include <vector>
#include "Event.h"
#include "Person.h"

class FileRepo {
    std::string eventsFile;
    std::string peopleFile;
public:
    FileRepo(const std::string& eventsFile, const std::string& peopleFile);

    std::vector<Event> loadEvents();
    void saveEvents(const std::vector<Event>& events);
    std::vector<Person> loadPeople();
};