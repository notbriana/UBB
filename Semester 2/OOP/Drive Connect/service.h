#pragma once
#include "domain.h"
#include <vector>
#include <functional>
#include "filerepo.h"

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Service {
    std::vector<Driver> drivers;
    std::vector<Report> reports;
    std::vector<Message> chat;
    std::vector<Observer*> observers;
    FileRepo& repo;

public:
    Service(FileRepo& repo, const std::vector<Driver>& d, const std::vector<Report>& r);
    const std::vector<Driver>& getDrivers() const;
    const std::vector<Report>& getReports() const;
    const std::vector<Message>& getChat() const;
    void addReport(const Report& report);
    void validateReport(int reportIdx, const std::string& driverName);
    void addMessage(const Message& msg);
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
    void notify();
    void saveReports(FileRepo& repo);
    void saveDrivers();
};