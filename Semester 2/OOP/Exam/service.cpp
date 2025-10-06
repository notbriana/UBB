#include "service.h"
#include <algorithm>
#include <stdexcept>
#include <set>
#include <sstream>
#include <fstream>

Service::Service(FileRepo& r): repo(r)
{
	departments = repo.loadDepartments();
	volunteers = repo.loadVolunteers();

}

const std::vector<Department>& Service::getDepartments() const 
{ 
	return departments;
}

std::vector<Volunteer> Service::getVolunteersPerDepartment(const std::string& dept) const
{
    std::vector<Volunteer> result;
    for (const auto& v : volunteers)
        if (v.getDepartment() == dept)
            result.push_back(v);
    std::sort(result.begin(), result.end(), [](const Volunteer& a, const Volunteer& b) {
        return a.getName() < b.getName();
        });
    return result;
}


std::vector<Volunteer> Service::getVolunteersUnassigned() const
{
    std::vector<Volunteer> result;
    for (const auto& v : volunteers)
        if (v.getDepartment().empty())
            result.push_back(v);
    std::sort(result.begin(), result.end(), [](const Volunteer& a, const Volunteer& b) {
        return a.getName() < b.getName();
        });
    return result;
}

void Service::addVolunteer(const std::string& name, const std::string& email, const std::vector<std::string>& interests)
{
    if (name.empty() || email.empty())
        throw std::runtime_error("Name and email cant be empty");
    volunteers.emplace_back(name, email, interests, "");
    save();
    notify();

}

void Service::assignVolunteer(const std::string& VolunterName, const std::string& department)
{
    for (auto& v : volunteers)
        if (v.getName() == VolunterName && v.getDepartment().empty()) {
             v.setDepartment(department);
             save();
             notify();
             return;
        }
}




void Service::save() {
    repo.saveVolunteers(volunteers);
}

void Service::notify()
{
    for (auto obs : observers) 
        obs->update();
}

void Service::addObserver(Observer* obs)
{
    observers.push_back(obs);
}

void Service::removeObserver(Observer* obs)
{
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());

}
