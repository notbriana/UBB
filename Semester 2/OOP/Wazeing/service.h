#pragma once
#include "filerepo.h"
#include "domain.h"
#include <QObject>
#include <vector>
#include <string>

class Service : public QObject {
    Q_OBJECT
private:
    FileRepo& repo;
public:
    Service(FileRepo& repo);

    std::vector<Driver> getAllDrivers() const;
    Driver getDriver(const std::string& name) const;

    std::vector<Report> getReportsInRadius(double lat, double lon, double radius) const;

    void addReport(const std::string& desc, const std::string& reporter, double lat, double lon);
    void validateReport(const Report& report, const std::string& validator);
    void moveDriver(const std::string& name, int dLat, int dLon);

    void saveAll();

signals:
    void dataChanged();
};