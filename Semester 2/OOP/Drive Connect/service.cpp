#include "service.h"

Service::Service(FileRepo& repo, const std::vector<Driver>& d, const std::vector<Report>& r)
    : drivers(d), reports(r), repo(repo) {}

const std::vector<Driver>& Service::getDrivers() const { return drivers; }
const std::vector<Report>& Service::getReports() const { return reports; }
const std::vector<Message>& Service::getChat() const { return chat; }

void Service::addReport(const Report& report) {
    reports.push_back(report);
    notify();
}

void Service::validateReport(int idx, const std::string& driverName) {
    if (idx < 0 || idx >= (int)reports.size()) return;
    auto& r = reports[idx];
    if (r.isValidated()) return;
    if (r.getReporter() == driverName) return;
    if (std::find(r.getValidators().begin(), r.getValidators().end(), driverName) == r.getValidators().end())
        r.validators.push_back(driverName);
    if (r.getValidators().size() >= 2 && !r.isValidated()) {
        r.setValidated(true);
        // Increment reporter's score
        for (auto& d : drivers)
            if (d.getName() == r.getReporter()) {
                d.setScore(d.getScore() + 1);
                saveDrivers(); // Save immediately after score update
                break;
            }
    }
    notify();
}

void Service::addMessage(const Message& msg) {
    chat.push_back(msg);
    notify();
}

void Service::addObserver(Observer* obs) { observers.push_back(obs); }
void Service::removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
void Service::notify() {
    for (auto obs : observers) obs->update();
}

void Service::saveReports(FileRepo& repo) {
    repo.saveReports(reports);
}

void Service::saveDrivers() {
    repo.saveDrivers(drivers);
}