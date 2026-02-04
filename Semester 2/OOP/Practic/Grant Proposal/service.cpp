#include "service.h"
#include <algorithm>
#include <fstream>

Service::Service(FileRepo& r) : repo(r) {
    researchers = repo.loadResearchers();
    ideas = repo.loadIdeas();
}

const std::vector<Researcher>& Service::getResearchers() const { return researchers; }

std::vector<Idea> Service::getIdeasSorted() const {
    auto sorted = ideas;
    std::sort(sorted.begin(), sorted.end(), [](const Idea& a, const Idea& b) {
        return a.duration < b.duration;
    });
    return sorted;
}

void Service::addIdea(const std::string& title, const std::string& desc, const std::string& creator, int duration) {
    if (title.empty() || (duration < 1 || duration > 3)) throw std::runtime_error("Invalid input");
    ideas.emplace_back(title, desc, "proposed", creator, duration);
    repo.saveIdeas(ideas);
    notify();
}

void Service::acceptIdea(const std::string& title, const std::string& researcherName) {
    // Find the researcher
    auto it = std::find_if(researchers.begin(), researchers.end(),
        [&](const Researcher& r) { return r.name == researcherName; });
    if (it == researchers.end() || it->position != "senior")
        throw std::runtime_error("Only senior researchers can accept ideas");

    for (auto& idea : ideas) {
        if (idea.title == title && idea.status == "proposed") {
            idea.status = "accepted";
            repo.saveIdeas(ideas);
            notify();
            return;
        }
    }
    throw std::runtime_error("Idea not found or already accepted");
}

void Service::updateIdeaDescription(const std::string& title, const std::string& newDesc) {
    for (auto& idea : ideas) {
        if (idea.title == title && idea.status == "accepted") {
            idea.description = newDesc;
            repo.saveIdeas(ideas);
            notify();
            return;
        }
    }
    throw std::runtime_error("Idea not found or not accepted");
}

void Service::saveIdeaToFile(const Idea& idea) {
    std::ofstream fout(idea.title + ".txt");
    fout << idea.title << "\n" << idea.description << "\n";
}

void Service::saveAllAcceptedIdeas(const std::string& filename) {
    auto sorted = getIdeasSorted();
    std::ofstream fout(filename);
    for (const auto& idea : sorted) {
        if (idea.status == "accepted") {
            fout << idea.title << " (" << idea.creator << "), "
                 << idea.duration << ", "
                 << idea.description << "\n";
        }
    }
}

void Service::addObserver(std::function<void()> obs) { observers.push_back(obs); }
void Service::notify() { for (auto& obs : observers) obs(); }