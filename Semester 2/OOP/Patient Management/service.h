#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <functional>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Service {
    FileRepo& repo;
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Observer*> observers;
public:
    Service(FileRepo& r);
    const std::vector<Doctor>& getDoctors() const;
    const std::vector<Patient>& getPatients() const;
    std::vector<Patient> getPatientsForDoctor(const Doctor& doc, bool onlyMine) const;
    void addPatient(const Patient& p);
    void updatePatient(const std::string& name, const std::string& newDiag, const std::string& newSpec, const std::string& doctorName);
    void save();
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
private:
    void notify();
};