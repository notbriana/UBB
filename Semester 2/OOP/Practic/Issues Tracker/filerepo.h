#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string usersFile, issuesFile;
    std::vector<User> users;
    std::vector<Issue> issues;
public:
    FileRepo(const std::string& uf, const std::string& ifile);
    void load();
    void saveIssues();
    const std::vector<User>& getUsers() const;
    const std::vector<Issue>& getIssues() const;
    void addIssue(const Issue& issue);
    void removeIssue(const std::string& description);
    void updateIssue(const Issue& issue);
};