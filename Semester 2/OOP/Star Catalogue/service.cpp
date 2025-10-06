#include "service.h"
#include <algorithm>

const std::vector<Astronomer>& Service::getAstronomers() const { return repo.getAstronomers(); }

std::vector<Star> Service::getStarsSorted() const {
    auto stars = repo.getStars();
    std::sort(stars.begin(), stars.end(), [](const Star& a, const Star& b) {
        if (a.constellation != b.constellation)
            return a.constellation < b.constellation;
        return a.name < b.name;
    });
    return stars;
}

std::vector<Star> Service::getStarsByConstellation(const std::string& c) const {
    std::vector<Star> result;
    for (const auto& s : repo.getStars())
        if (s.constellation == c)
            result.push_back(s);
    return result;
}

bool Service::addStar(const std::string& name, const std::string& constellation, int ra, int dec, double dia) {
    if (name.empty()) return false;
    for (const auto& s : repo.getStars())
        if (s.name == name) return false;
    auto stars = repo.getStars();
    stars.emplace_back(name, constellation, ra, dec, dia);
    repo.setStars(stars);
    notify();
    save();
    return true;
}

bool Service::updateStar(const std::string& oldName, const std::string& newName, int ra, int dec, double dia) {
    if (newName.empty() || dia <= 10) return false;
    auto stars = repo.getStars();
    for (auto& s : stars) {
        if (s.name == oldName) {
            s.name = newName;
            s.ra = ra;
            s.dec = dec;
            s.diameter = dia;
            repo.setStars(stars);
            notify();
            save();
            return true;
        }
    }
    return false;
}

void Service::addObserver(std::function<void()> obs) { observers.push_back(obs); }
void Service::notify() { for (auto& obs : observers) obs(); }
void Service::save() { repo.save(); }

std::vector<Star> Service::searchStars(const std::string& namePart) const {
    std::vector<Star> result;
    for (const auto& s : repo.getStars())
        if (s.name.find(namePart) != std::string::npos)
            result.push_back(s);
    return result;
}