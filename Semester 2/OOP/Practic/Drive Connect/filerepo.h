#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
public:
    FileRepo(const std::string& driversFile, const std::string& reportsFile);
    std::vector<Driver> loadDrivers();
    std::vector<Report> loadReports();
    void saveReports(const std::vector<Report>& reports);
    void saveDrivers(const std::vector<Driver>& drivers);
private:
    std::string driversFile, reportsFile;
};