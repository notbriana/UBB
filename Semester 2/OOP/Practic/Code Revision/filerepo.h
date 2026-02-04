#pragma once

#include "domain.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository {
private:
    std::vector<Programmer> programmers;
    std::vector<SourceFile> files;

public:
    void loadProgrammers(const std::string& filename);
    void loadFiles(const std::string& filename);
    std::vector<Programmer>& getProgrammers();
    std::vector<SourceFile>& getFiles();
    const std::vector<Programmer>& getAllProgrammers() const;
};