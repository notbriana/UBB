#include "service.h"
#include <algorithm>

CodeRevisionService::CodeRevisionService(Repository& r) : repo(r) {}

std::vector<SourceFile> CodeRevisionService::getAllFiles() const {
    return repo.getFiles();
}

std::vector<SourceFile> CodeRevisionService::getFilesSorted() const {
    auto files = repo.getFiles();
    std::sort(files.begin(), files.end(), [](const SourceFile& a, const SourceFile& b) {
        return a.name < b.name;
        });
    return files;
}

std::vector<Programmer> CodeRevisionService::getAllProgrammers() const {
    auto programmers = repo.getAllProgrammers();
    auto files = getAllFiles();

    for (auto& prog : programmers) {
        int count = std::count_if(files.begin(), files.end(),
            [&prog](const SourceFile& file) {
                return file.reviewer == prog.name;
            });
        prog.revised_files = count;
    }
    return programmers;
}

void CodeRevisionService::reviseFile(const std::string& fileName, const std::string& reviewer) {
    for (auto& file : repo.getFiles()) {
        if (file.name == fileName && file.status == "not_revised" && file.creator != reviewer) {
            file.status = "revised";
            file.reviewer = reviewer;
            for (auto& programmer : repo.getProgrammers()) {
                if (programmer.name == reviewer) {
                    programmer.revised_files++;
                }
            }
            notify();
            break;
        }
    }
}

void CodeRevisionService::addObserver(std::function<void()> obs) {
    observers.push_back(obs);
}

void CodeRevisionService::notify() {
    for (auto& obs : observers) {
        obs();
    }
}

bool CodeRevisionService::addFile(const std::string& name, const std::string& creator, std::string& error) {
    if (name.empty()) {
        error = "File name cannot be empty!";
        return false;
    }

    for (const auto& file : repo.getFiles()) {
        if (file.name == name) {
            error = "A file with this name already exists!";
            return false;
        }
    }

    repo.getFiles().emplace_back(name, "not_revised", creator, "");
    notify();
    return true;
}
