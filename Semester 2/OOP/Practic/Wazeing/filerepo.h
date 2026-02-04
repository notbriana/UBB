#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
private:
    std::string driversFile;
    std::string reportsFile;
    std::vector<Driver> drivers;
    std::vector<Report> reports;

public:
    FileRepo(const std::string& driversFile, const std::string& reportsFile);

    void loadFromFiles();
    void saveToFiles();

    std::vector<Driver>& getDrivers();
    const std::vector<Driver>& getDrivers() const;
    std::vector<Report>& getReports();
    const std::vector<Report>& getReports() const;
};