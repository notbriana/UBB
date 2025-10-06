#include "service.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>

const std::vector<Writer>& Service::getWriters() const { return repo.getWriters(); }

std::vector<Idea> Service::getIdeasSorted() const {
    auto ideas = repo.getIdeas();
    std::sort(ideas.begin(), ideas.end(), [](const Idea& a, const Idea& b) {
        return a.getAct() < b.getAct();
    });
    return ideas;
}

void Service::addIdea(const std::string& desc, const std::string& creator, int act) {
    if (desc.empty()) throw std::runtime_error("Description cannot be empty.");
    if (act < 1 || act > 3) throw std::runtime_error("Act must be 1, 2, or 3.");
    for (const auto& idea : repo.getIdeas()) {
        if (idea.getDescription() == desc && idea.getAct() == act)
            throw std::runtime_error("Duplicate idea in the same act.");
    }
    auto ideas = repo.getIdeas();
    ideas.emplace_back(desc, "proposed", creator, act);
    repo.setIdeas(ideas);
    repo.saveIdeas();
}

void Service::acceptIdea(const std::string& desc, int act, const std::string& user) {
    auto ideas = repo.getIdeas();
    bool found = false;
    for (auto& idea : ideas) {
        if (idea.getDescription() == desc && idea.getAct() == act) {
            if (idea.getStatus() != "proposed")
                throw std::runtime_error("Idea is not proposed.");
            idea.setStatus("accepted");
            found = true;
            break;
        }
    }
    if (!found) throw std::runtime_error("Idea not found.");
    repo.setIdeas(ideas);
    repo.saveIdeas();
}

void Service::developIdea(const std::string& desc, int act, const std::string& devText, const std::string& user) {
    auto ideas = repo.getIdeas();
    bool found = false;
    for (auto& idea : ideas) {
        if (idea.getDescription() == desc && idea.getAct() == act && idea.getCreator() == user && idea.getStatus() == "accepted") {
            idea.setDevelopment(devText);
            found = true;
            break;
        }
    }
    if (!found) throw std::runtime_error("Accepted idea not found for development.");
    repo.setIdeas(ideas);
    repo.saveIdeas();
}

void Service::saveIdeas() { repo.saveIdeas(); }

void Service::savePlot(const std::string& filename) {
    std::ofstream fout(filename);
    for (int act = 1; act <= 3; ++act) {
        fout << "Act " << act << ":\n";
        for (const auto& idea : repo.getIdeas()) {
            if (idea.getAct() == act && idea.getStatus() == "accepted") {
                fout << idea.getDescription() << " (" << idea.getCreator() << ")\n";
            }
        }
    }
    fout.close();
}