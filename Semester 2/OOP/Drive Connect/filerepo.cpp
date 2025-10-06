#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& d, const std::string& r) : driversFile(d), reportsFile(r) {}

std::vector<Driver> FileRepo::loadDrivers() {
    std::vector<Driver> drivers;
    std::ifstream fin(driversFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        Driver d;
        iss >> d.name >> d.latitude >> d.longitude >> d.score;
        drivers.push_back(d);
    }
    return drivers;
}

std::vector<Report> FileRepo::loadReports() {
    std::vector<Report> reports;
    std::ifstream fin(reportsFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        Report r;
        iss >> r.description >> r.reporter >> r.latitude >> r.longitude >> r.validated;
        reports.push_back(r);
    }
    return reports;
}

void FileRepo::saveReports(const std::vector<Report>& reports) {
    std::ofstream fout(reportsFile);
    for (const auto& r : reports) {
        fout << r.description << " " << r.reporter << " " << r.latitude << " " << r.longitude << " " << r.validated << "\n";
    }
}

void FileRepo::saveDrivers(const std::vector<Driver>& drivers) {
    std::ofstream fout(driversFile);
    for (const auto& d : drivers) {
        fout << d.getName() << " " << d.getLatitude() << " " << d.getLongitude() << " " << d.getScore() << "\n";
    }
}