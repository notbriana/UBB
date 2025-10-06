#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::vector<Writer> writers;
    std::vector<Idea> ideas;
    std::string writersFile, ideasFile;
public:
    FileRepo(const std::string& wf, const std::string& ifile);
    void load();
    void saveIdeas();
    const std::vector<Writer>& getWriters() const;
    const std::vector<Idea>& getIdeas() const;
    void setIdeas(const std::vector<Idea>& newIdeas);
};