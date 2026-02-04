#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::vector<Astronomer> astronomers;
    std::vector<Star> stars;
    std::string astronomersFile, starsFile;
public:
    FileRepo(const std::string& aFile, const std::string& sFile);
    void load();
    void save();
    const std::vector<Astronomer>& getAstronomers() const;
    const std::vector<Star>& getStars() const;
    void setStars(const std::vector<Star>& newStars);
};