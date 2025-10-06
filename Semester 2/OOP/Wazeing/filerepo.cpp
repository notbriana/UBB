#include "filerepo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

FileRepo::FileRepo(const std::string& driversFile, const std::string& reportsFile)
    : driversFile(driversFile), reportsFile(reportsFile) {
    loadFromFiles();
}

void FileRepo::loadFromFiles() {
    // Load drivers
    drivers.clear();
    std::ifstream fin(driversFile);
    if (!fin) throw std::runtime_error("Cannot open drivers file");
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, statusStr;
        double lat, lon;
        int score;
        if (!(iss >> name >> statusStr >> lat >> lon >> score)) continue;
        Status status;
        if (statusStr == "baby") status = Status::Baby;
        else if (statusStr == "grown-up") status = Status::GrownUp;
        else status = Status::Knight;
        drivers.emplace_back(name, status, Location(lat, lon), score);
    }
    fin.close();

    // Load reports
    reports.clear();
    std::ifstream fin2(reportsFile);
    if (!fin2) throw std::runtime_error("Cannot open reports file");
    while (std::getline(fin2, line)) {
        std::istringstream iss(line);
        std::string desc, reporter;
        double lat, lon;
        int validated, validations;
        if (!(iss >> std::ws) || iss.peek() == EOF) continue;
        std::getline(iss, desc, '|');
        if (!(iss >> reporter >> lat >> lon >> validated >> validations)) continue;
        reports.emplace_back(desc, reporter, Location(lat, lon), validated != 0, validations);
    }
    fin2.close();
}

void FileRepo::saveToFiles() {
    // Save drivers
    std::ofstream fout(driversFile);
    for (const auto& d : drivers) {
        fout << d.name << " " << d.getStatus() << " " << d.location.lat << " " << d.location.lon << " " << d.score << "\n";
    }
    fout.close();

    // Save reports
    std::ofstream fout2(reportsFile);
    for (const auto& r : reports) {
        fout2 << r.description << "|" << r.reporter << " " << r.location.lat << " " << r.location.lon << " "
              << (r.validated ? 1 : 0) << " " << r.validations << "\n";
    }
    fout2.close();
}

std::vector<Driver>& FileRepo::getDrivers() {
    return drivers;
}

const std::vector<Driver>& FileRepo::getDrivers() const {
    return drivers;
}

std::vector<Report>& FileRepo::getReports() {
    return reports;
}

const std::vector<Report>& FileRepo::getReports() const {
    return reports;
}

