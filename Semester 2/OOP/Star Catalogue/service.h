#pragma once
#include "filerepo.h"
#include <vector>
#include <string>
#include <functional>

class Service {
    FileRepo& repo;
    std::vector<std::function<void()>> observers;
public:
    Service(FileRepo& r) : repo(r) {}
    const std::vector<Astronomer>& getAstronomers() const;
    std::vector<Star> getStarsSorted() const;
    std::vector<Star> getStarsByConstellation(const std::string& c) const;
    bool addStar(const std::string& name, const std::string& constellation, int ra, int dec, double dia);
    bool updateStar(const std::string& oldName, const std::string& newName, int ra, int dec, double dia);
    void addObserver(std::function<void()> obs);
    void notify();
    void save();
    std::vector<Star> searchStars(const std::string& namePart) const;
};