#include "Service.h"
#include <set>

Service::Service(FileRepo& repo) : repo(repo) {}

std::vector<Courier> Service::getCouriers() const {
    return repo.getCouriers();  // <-- assuming repo stores couriers
}

std::vector<Package> Service::getAllPackages() const {
    return repo.getPackages();
}

std::vector<Package> Service::getPackagesForCourier(const Courier& c) const {
    std::vector<Package> result;
    std::set<std::string> seen; // To avoid duplicates, use a set of unique package keys
    for (const auto& p : repo.getPackages()) {
        if (!p.isDelivered()) {
            bool assigned = false;
            // Check if street matches
            for (const auto& s : c.getStreets()) {
                if (p.getStreet() == s) {
                    assigned = true;
                    break;
                }
            }
            // Or check if location is in zone
            if (!assigned && c.isInZone(p.getX(), p.getY())) {
                assigned = true;
            }
            if (assigned) {
                // Create a unique key for the package (recipient+address+x+y)
                std::string key = p.getRecipient() + "|" + p.getAddress() + "|" +
                                  std::to_string(p.getX()) + "|" + std::to_string(p.getY());
                if (seen.find(key) == seen.end()) {
                    result.push_back(p);
                    seen.insert(key);
                }
            }
        }
    }
    return result;
}

void Service::saveToFile() {
    repo.writePackagesToFile();
}
