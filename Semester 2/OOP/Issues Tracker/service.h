#pragma once
#include "filerepo.h"
#include <vector>
#include <functional>

class Service {
    FileRepo& repo;
    std::vector<std::function<void()>> observers;
public:
    Service(FileRepo& r) : repo(r) {}
    const std::vector<User>& getUsers() const { return repo.getUsers(); }
    std::vector<Issue> getSortedIssues() const;
    void addIssue(const std::string& desc, const std::string& reporter);
    void removeIssue(const std::string& desc);
    void resolveIssue(const std::string& desc, const std::string& solver);
    void addObserver(std::function<void()> obs);
    void notify();
    void save() { repo.saveIssues(); }
};