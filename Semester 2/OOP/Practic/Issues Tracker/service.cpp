#include "service.h"
#include <algorithm>
#include <stdexcept>

std::vector<Issue> Service::getSortedIssues() const {
    auto issues = repo.getIssues();
    std::sort(issues.begin(), issues.end(), [](const Issue& a, const Issue& b) {
        if (a.status != b.status) return a.status < b.status;
        return a.description < b.description;
    });
    return issues;
}

void Service::addIssue(const std::string& desc, const std::string& reporter) {
    if (desc.empty()) throw std::runtime_error("Description cannot be empty.");
    for (const auto& i : repo.getIssues())
        if (i.description == desc)
            throw std::runtime_error("Duplicate description.");
    repo.addIssue(Issue(desc, "open", reporter, ""));
    save();
    notify();
}

void Service::removeIssue(const std::string& desc) {
    auto issues = repo.getIssues();
    auto it = std::find_if(issues.begin(), issues.end(), [&](const Issue& i) { return i.description == desc; });
    if (it == issues.end()) throw std::runtime_error("Issue not found.");
    if (it->status != "closed") throw std::runtime_error("Only closed issues can be removed.");
    repo.removeIssue(desc);
    save();
    notify();
}

void Service::resolveIssue(const std::string& desc, const std::string& solver) {
    auto issues = repo.getIssues();
    auto it = std::find_if(issues.begin(), issues.end(), [&](const Issue& i) { return i.description == desc; });
    if (it == issues.end()) throw std::runtime_error("Issue not found.");
    if (it->status != "open") throw std::runtime_error("Only open issues can be resolved.");
    Issue updated = *it;
    updated.status = "closed";
    updated.solver = solver;
    repo.updateIssue(updated);
    save();
    notify();
}

void Service::addObserver(std::function<void()> obs) { observers.push_back(obs); }
void Service::notify() { for (auto& obs : observers) obs(); }