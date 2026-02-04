#include "filerepo.h"

void Repository::loadProgrammers(const std::string& filename) {
    std::ifstream fin(filename);
    std::string name;
    int revised, total;
    while (fin >> name >> revised >> total) {
        programmers.emplace_back(name, revised, total);
    }
}

void Repository::loadFiles(const std::string& filename) {
    std::ifstream fin(filename);
    std::string name, status, creator, reviewer;
    while (fin >> name >> status >> creator >> reviewer) {
        files.emplace_back(name, status, creator, reviewer);
    }
}

std::vector<Programmer>& Repository::getProgrammers() { return programmers; }
std::vector<SourceFile>& Repository::getFiles() { return files; }

const std::vector<Programmer>& Repository::getAllProgrammers() const {
    return programmers;
}
