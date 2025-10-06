#include "FileRepo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

FileRepo::FileRepo(const std::string& couriersFile, const std::string& packagesFile)
    : couriersFile(couriersFile), packagesFile(packagesFile) {
    loadFromFile();
}

void FileRepo::loadFromFile() {
    // Load couriers
    couriers.clear();
    std::ifstream finC(couriersFile);
    if (!finC.is_open()) throw std::runtime_error("Failed to open couriers file.");

    std::string line;
    while (getline(finC, line)) {
        std::stringstream ss(line);
        std::string name, streetsStr, zoneStr;

        getline(ss, name, ';');
        getline(ss, streetsStr, ';');
        getline(ss, zoneStr);

        std::vector<std::string> streets;
        std::stringstream ssStreets(streetsStr);
        std::string street;
        while (getline(ssStreets, street, ',')) {
            streets.push_back(street);
        }

        double x, y, r;
        std::stringstream ssZone(zoneStr);
        ssZone >> x >> y >> r;

        couriers.emplace_back(name, streets, x, y, r);
    }
    finC.close();

    // load packages
    packages.clear();
    std::ifstream finP(packagesFile);
    if (!finP.is_open()) throw std::runtime_error("Failed to open packages file.");

    while (getline(finP, line)) {
        std::stringstream ss(line);
        std::string recipient, address, coordStr, statusStr;

        getline(ss, recipient, ';');
        getline(ss, address, ';');   // street + number in one string, e.g. "Main Street 12"
        getline(ss, coordStr, ';');
        getline(ss, statusStr);

        double x, y;
        std::stringstream ssCoord(coordStr);
        ssCoord >> x >> y;

        bool delivered = (statusStr == "1");

        packages.emplace_back(recipient, address, x, y, delivered);
    }
    finP.close();

}


void FileRepo::writePackagesToFile() {
    std::ofstream fout(packagesFile);
    if (!fout.is_open()) throw std::runtime_error("Failed to write packages file.");

    for (const auto& p : packages) {
        fout << p.getRecipient() << ';'
            << p.getAddress() << ';'
            << p.getX() << ' ' << p.getY() << ';'
            << (p.isDelivered() ? "1" : "0") << '\n';
    }

    fout.close();
}


std::vector<Courier> FileRepo::getCouriers() const {
    return couriers;
}

std::vector<Package> FileRepo::getPackages() const {
    return packages;
}

void FileRepo::addPackage(const Package& p) {
    packages.push_back(p);
}

void FileRepo::updatePackageStatus(const Package& p, bool delivered) {
    for (auto& pkg : packages) {
        if (pkg == p) { // You must implement == operator in Package
            pkg.setDelivered(delivered);
            break;
        }
    }
}
