#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& rf, const std::string& ifile)
    : researchersFile(rf), ideasFile(ifile) {}

std::vector<Researcher> FileRepo::loadResearchers() {
    std::vector<Researcher> res;
    std::ifstream fin(researchersFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, position;
        getline(iss, name, ',');
        getline(iss, position);
        if (!name.empty() && !position.empty())
            res.emplace_back(name, position);
    }
    return res;
}

std::vector<Idea> FileRepo::loadIdeas() {
    std::vector<Idea> res;
    std::ifstream fin(ideasFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        std::string title, description, status, creator, durationStr;
        getline(iss, title, ',');
        getline(iss, description, ',');
        getline(iss, status, ',');
        getline(iss, creator, ',');
        getline(iss, durationStr);
        int duration = std::stoi(durationStr);
        if (!title.empty())
            res.emplace_back(title, description, status, creator, duration);
    }
    return res;
}

void FileRepo::saveIdeas(const std::vector<Idea>& ideas) {
    std::ofstream fout(ideasFile);
    for (const auto& idea : ideas) {
        fout << idea.title << "," << idea.description << "," << idea.status << ","
             << idea.creator << "," << idea.duration << "\n";
    }
}