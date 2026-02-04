#include "filerepo.h"
#include <fstream>
#include <algorithm>

FileRepo::FileRepo(const std::string& aFile, const std::string& sFile)
    : astronomersFile(aFile), starsFile(sFile) {}

void FileRepo::load() {
    astronomers.clear();
    stars.clear();
    std::ifstream finA(astronomersFile), finS(starsFile);
    std::string name, constellation;
    while (finA >> name >> constellation)
        astronomers.emplace_back(name, constellation);
    while (finS >> name >> constellation) {
        int ra, dec;
        double dia;
        finS >> ra >> dec >> dia;
        stars.emplace_back(name, constellation, ra, dec, dia);
    }
}

void FileRepo::save() {
    std::ofstream fout(starsFile);
    std::vector<Star> sortedStars = stars;
    std::sort(sortedStars.begin(), sortedStars.end(), [](const Star& a, const Star& b) {
        if (a.constellation != b.constellation)
            return a.constellation < b.constellation;
        return a.diameter > b.diameter;
    });
    for (const auto& s : sortedStars)
        fout << s.name << " " << s.constellation << " " << s.ra << " " << s.dec << " " << s.diameter << "\n";
}

const std::vector<Astronomer>& FileRepo::getAstronomers() const { return astronomers; }
const std::vector<Star>& FileRepo::getStars() const { return stars; }
void FileRepo::setStars(const std::vector<Star>& newStars) { stars = newStars; }