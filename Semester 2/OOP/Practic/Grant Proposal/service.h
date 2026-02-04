#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <functional>

class Service {
    FileRepo& repo;
    std::vector<Researcher> researchers;
    std::vector<Idea> ideas;
    std::vector<std::function<void()>> observers;
public:
    Service(FileRepo& r);
    const std::vector<Researcher>& getResearchers() const;
    std::vector<Idea> getIdeasSorted() const;
    void addIdea(const std::string& title, const std::string& desc, const std::string& creator, int duration);
    void acceptIdea(const std::string& title, const std::string& researcherName);
    void updateIdeaDescription(const std::string& title, const std::string& newDesc);
    void saveIdeaToFile(const Idea& idea);
    void saveAllAcceptedIdeas(const std::string& filename);
    void addObserver(std::function<void()> obs);
    void notify();

};