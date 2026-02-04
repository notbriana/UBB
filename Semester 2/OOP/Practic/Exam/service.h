#pragma once
#include "filerepo.h"
#include <vector>
#include <string>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Service {

    FileRepo& repo;
    std::vector<Department> departments;
    std::vector<Volunteer> volunteers;
    std::vector<Observer*> observers;

public:
    Service(FileRepo& r);
    const std::vector<Department>& getDepartments() const;
    std::vector<Volunteer> getVolunteersPerDepartment(const std::string& dept) const;
    std::vector<Volunteer> getVolunteersUnassigned() const;
    void addVolunteer(const std::string& name, const std::string& email, const std::vector<std::string>& interests);
    void assignVolunteer(const std::string& VolunterName, const std::string& department);

    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
    void notify();
    void save();
};