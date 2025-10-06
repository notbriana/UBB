#include "FileRepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& eventsFile, const std::string& peopleFile)
    : eventsFile(eventsFile), peopleFile(peopleFile) {}

std::vector<Event> FileRepo::loadEvents() {
    std::vector<Event> events;
    std::ifstream fin(eventsFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string organiser, name, description, date;
        double lat, lon;
        iss >> organiser >> name >> lat >> lon >> date;
        std::getline(fin, description);
        Event ev(organiser, name, description, {lat, lon}, date);
        // Optionally, read attendees from file
        events.push_back(ev);
    }
    return events;
}

void FileRepo::saveEvents(const std::vector<Event>& events) {
    std::ofstream fout(eventsFile);
    for (const auto& ev : events) {
        fout << ev.getOrganiser() << " " << ev.getName() << " "
             << ev.getLocation().latitude << " " << ev.getLocation().longitude << " "
             << ev.getDate() << "\n" << ev.getDescription() << "\n";
        // Optionally, write attendees
    }
}

std::vector<Person> FileRepo::loadPeople() {
    std::vector<Person> people;
    std::ifstream fin(peopleFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name;
        double lat, lon;
        int isOrg;
        iss >> name >> lat >> lon >> isOrg;
        people.emplace_back(name, Location{lat, lon}, isOrg != 0);
    }
    return people;
}