#include "service.h"
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

Service::Service(FileRepo& r) : repo(r) {
    departments = repo.loadDepartments();
    volunteers = repo.loadVolunteers();
}

const std::vector<Department>& Service::getDepartments() const { return departments; }

std::vector<Volunteer> Service::getVolunteersForDepartment(const std::string& dept) const {
    std::vector<Volunteer> res;
    for (const auto& v : volunteers)
        if (v.getDepartment() == dept)
            res.push_back(v);
    std::sort(res.begin(), res.end(), [](const Volunteer& a, const Volunteer& b) {
        return a.getName() < b.getName();
    });
    return res;
}

std::vector<Volunteer> Service::getUnassignedVolunteers() const {
    std::vector<Volunteer> res;
    for (const auto& v : volunteers)
        if (v.getDepartment().empty())
            res.push_back(v);
    std::sort(res.begin(), res.end(), [](const Volunteer& a, const Volunteer& b) {
        return a.getName() < b.getName();
    });
    return res;
}

void Service::addVolunteer(const std::string& name, const std::string& email, const std::vector<std::string>& interests) {
    if (name.empty() || email.empty()) throw std::runtime_error("Name and email cannot be empty");
    volunteers.emplace_back(name, email, interests, "");
    notify();
}

void Service::assignVolunteer(const std::string& volunteerName, const std::string& dept) {
    for (auto& v : volunteers)
        if (v.getName() == volunteerName && v.getDepartment().empty()) {
            v.setDepartment(dept);
            notify();
            return;
        }
}

std::vector<Volunteer> Service::top3Suitable(const std::string& dept) const {
    auto it = std::find_if(departments.begin(), departments.end(), [&](const Department& d) { return d.getName() == dept; });
    if (it == departments.end()) return {};
    std::set<std::string> descWords;
    std::stringstream ss(it->getDescription());
    std::string word;
    while (ss >> word) descWords.insert(word);

    std::vector<std::pair<Volunteer, double>> scored;
    for (const auto& v : getUnassignedVolunteers()) {
        int match = 0;
        for (const auto& interest : v.getInterests())
            if (descWords.count(interest)) ++match;
        double score = descWords.empty() ? 0.0 : (double)match / descWords.size();
        scored.emplace_back(v, score);
    }
    std::sort(scored.begin(), scored.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    std::vector<Volunteer> res;
    for (size_t i = 0; i < 3 && i < scored.size(); ++i)
        res.push_back(scored[i].first);
    return res;
}

void Service::addObserver(Observer* obs) { observers.push_back(obs); }
void Service::removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
void Service::notify() { for (auto obs : observers) obs->update(); }
void Service::save() { repo.saveVolunteers(volunteers); }