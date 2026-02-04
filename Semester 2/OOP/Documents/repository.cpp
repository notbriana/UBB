#include "repository.h"
#include <fstream>
#include <sstream>

Repository::Repository() {
    loadFromFile();
}

void Repository::loadFromFile() {
    std::ifstream file("documents.txt");
    std::string line;
    const char del = '|';
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, keywords, content;
        std::getline(iss, name, del);
        std::getline(iss, keywords, del);
        std::getline(iss, content, del);
        documents.emplace_back(name, keywords, content);
    }
}

std::vector<Document> Repository::getAllDocuments() {
    return documents;
}
