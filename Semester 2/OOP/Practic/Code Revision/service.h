#pragma once
#include "filerepo.h"
#include <functional>
#include <vector>

class CodeRevisionService {
private:
    Repository& repo;
    std::vector<std::function<void()>> observers;

public:
    CodeRevisionService(Repository& r);
    std::vector<SourceFile> getAllFiles() const;
    std::vector<SourceFile> getFilesSorted() const;
    void reviseFile(const std::string& fileName, const std::string& reviewer);
    void addObserver(std::function<void()> obs);
    void notify();
    bool addFile(const std::string& name, const std::string& creator, std::string& error);
    std::vector<Programmer> getAllProgrammers() const;

};
