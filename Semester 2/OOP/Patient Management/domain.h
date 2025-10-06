#pragma once
#include <string>
#include <vector>
#include <ctime>

class Doctor {
    std::string name;
    std::string specialisation;
public:
    Doctor(const std::string& n, const std::string& s) : name(n), specialisation(s) {}
    const std::string& getName() const { return name; }
    const std::string& getSpecialisation() const { return specialisation; }
};

class Patient {
    std::string name;
    std::string diagnosis;
    std::string neededSpecialisation;
    std::string currentDoctor;
    std::string admissionDate; // Format: YYYY-MM-DD
public:
    Patient(const std::string& n, const std::string& d, const std::string& ns, const std::string& cd, const std::string& ad)
        : name(n), diagnosis(d), neededSpecialisation(ns), currentDoctor(cd), admissionDate(ad) {}
    const std::string& getName() const { return name; }
    const std::string& getDiagnosis() const { return diagnosis; }
    const std::string& getNeededSpecialisation() const { return neededSpecialisation; }
    const std::string& getCurrentDoctor() const { return currentDoctor; }
    const std::string& getAdmissionDate() const { return admissionDate; }

    void setDiagnosis(const std::string& d) { diagnosis = d; }
    void setNeededSpecialisation(const std::string& ns) { neededSpecialisation = ns; }
    void setCurrentDoctor(const std::string& cd) { currentDoctor = cd; }
};