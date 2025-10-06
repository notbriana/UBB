#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string researchersFile, ideasFile;
public:
    FileRepo(const std::string& rf, const std::string& ifile);
    std::vector<Researcher> loadResearchers();
    std::vector<Idea> loadIdeas();
    void saveIdeas(const std::vector<Idea>& ideas);
};