#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
private:
    std::string couriersFile;
    std::string packagesFile;
    std::vector<Courier> couriers;
    std::vector<Package> packages;

public:
    FileRepo(const std::string& cFile, const std::string& pFile);

    void loadFromFile();
    void writePackagesToFile();

    std::vector<Courier> getCouriers() const;     // <-- ADD THIS
    std::vector<Package> getPackages() const;

    void addPackage(const Package& p);
    void updatePackageStatus(const Package& p, bool delivered);
};
