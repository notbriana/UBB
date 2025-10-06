#include "service.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

Service::Service(FileRepo& r) : QObject(), repo(r) {}

std::vector<Driver> Service::getAllDrivers() const {
    return repo.getDrivers();
}

Driver Service::getDriver(const std::string& name) const {
    for (const auto& d : repo.getDrivers()) {
        if (d.name == name)
            return d;
    }
    throw std::runtime_error("Driver not found");
}

std::vector<Report> Service::getReportsInRadius(double lat, double lon, double radius) const {
    std::vector<Report> result;
    for (const auto& r : repo.getReports()) {
        double dist = std::sqrt((lat - r.location.lat) * (lat - r.location.lat) +
                                (lon - r.location.lon) * (lon - r.location.lon));
        if (dist <= radius)
            result.push_back(r);
    }
    return result;
}

void Service::addReport(const std::string& desc, const std::string& reporter, double lat, double lon) {
    if (desc.empty())
        throw std::runtime_error("Description cannot be empty.");
    Driver d = getDriver(reporter);
    double dist = std::sqrt((lat - d.location.lat) * (lat - d.location.lat) +
                            (lon - d.location.lon) * (lon - d.location.lon));
    if (dist > 20)
        throw std::runtime_error("Report location too far from your location.");
    repo.getReports().push_back(Report(desc, reporter, Location(lat, lon), false, 0));
    emit dataChanged();
}

void Service::validateReport(const Report& report, const std::string& validator) {
    if (report.reporter == validator || report.validated)
        throw std::runtime_error("Cannot validate this report.");

    // Find the report in the repo and update it
    for (auto& r : repo.getReports()) {
        if (r.description == report.description &&
            r.reporter == report.reporter &&
            r.location.lat == report.location.lat &&
            r.location.lon == report.location.lon) {
            if (r.validated)
                throw std::runtime_error("Report already validated.");
            if (r.reporter == validator)
                throw std::runtime_error("Reporter cannot validate their own report.");
            r.validations++;
            if (r.validations >= 2) {
                r.validated = true;
                // Update reporter's score and status
                for (auto& d : repo.getDrivers()) {
                    if (d.name == r.reporter) {
                        d.score++;
                        if (d.score >= 15)
                            d.status = Status::Knight;
                        else if (d.score >= 10)
                            d.status = Status::GrownUp;
                    }
                }
            }
            emit dataChanged();
            return;
        }
    }
    throw std::runtime_error("Report not found.");
}

void Service::moveDriver(const std::string& name, int dLat, int dLon) {
    for (auto& d : repo.getDrivers()) {
        if (d.name == name) {
            d.location.lat += dLat;
            d.location.lon += dLon;
            emit dataChanged();
            return;
        }
    }
    throw std::runtime_error("Driver not found.");
}

void Service::saveAll() {
    repo.saveToFiles();
}
