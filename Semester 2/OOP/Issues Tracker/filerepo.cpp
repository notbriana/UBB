#include "filerepo.h"
#include <fstream>
#include <sstream>
#include <algorithm>

FileRepo::FileRepo(const std::string& uf, const std::string& ifile)
    : usersFile(uf), issuesFile(ifile) { load(); }

void FileRepo::load() {
    users.clear();
    issues.clear();
    std::ifstream fin(usersFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, type;
        if (std::getline(iss, name, ',') && std::getline(iss, type))
            users.emplace_back(name, type);
    }
    fin.close();

    std::ifstream fin2(issuesFile);
    while (std::getline(fin2, line)) {
        std::istringstream iss(line);
        std::string desc, status, reporter, solver;
        if (std::getline(iss, desc, ',') && std::getline(iss, status, ',') &&
            std::getline(iss, reporter, ',') && std::getline(iss, solver))
            issues.emplace_back(desc, status, reporter, solver);
    }
    fin2.close();
}

void FileRepo::saveIssues() {
    std::ofstream fout(issuesFile);
    for (const auto& i : issues)
        fout << i.description << "," << i.status << "," << i.reporter << "," << i.solver << "\n";
    fout.close();
}

const std::vector<User>& FileRepo::getUsers() const { return users; }
const std::vector<Issue>& FileRepo::getIssues() const { return issues; }

void FileRepo::addIssue(const Issue& issue) { issues.push_back(issue); }
void FileRepo::removeIssue(const std::string& description) {
    issues.erase(std::remove_if(issues.begin(), issues.end(),
        [&](const Issue& i) { return i.description == description; }), issues.end());
}
void FileRepo::updateIssue(const Issue& issue) {
    for (auto& i : issues)
        if (i.description == issue.description)
            i = issue;
}