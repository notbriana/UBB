#pragma once
#include "filerepo.h"
#include <vector>
#include <string>

class Service {
    FileRepo& repo;
public:
    Service(FileRepo& r) : repo(r) {}
    const std::vector<Writer>& getWriters() const;
    std::vector<Idea> getIdeasSorted() const;
    void addIdea(const std::string& desc, const std::string& creator, int act);
    void acceptIdea(const std::string& desc, int act, const std::string& user);
    void developIdea(const std::string& desc, int act, const std::string& devText, const std::string& user);
    void saveIdeas();
    void savePlot(const std::string& filename);
};