#pragma once
#include "filerepo.h"
#include "domain.h"
#include "observable.h"
#include <vector>

class Service : public Observable {
private:
    FileRepo& repo;

public:
    Service(FileRepo& repo);

    std::vector<Courier> getCouriers() const;               // <-- ADD THIS
    std::vector<Package> getAllPackages() const;
    std::vector<Package> getPackagesForCourier(const Courier& c) const;
    void deliverPackage(const Package& p) {
        repo.updatePackageStatus(p, true);
        notifyObservers();
    }
    void addPackage(const Package& p) {
        repo.addPackage(p);
        notifyObservers();
    }
    void saveToFile();  // for closing
};
