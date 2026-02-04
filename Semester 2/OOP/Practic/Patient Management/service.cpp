#include "service.h"
#include <algorithm>
#include <ctime>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <cctype>

// Helper to trim and lowercase a string
static std::string normalize(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    std::string trimmed = (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    std::string lower;
    std::transform(trimmed.begin(), trimmed.end(), std::back_inserter(lower),
                   [](unsigned char c){ return std::tolower(c); });
    return lower;
}

Service::Service(FileRepo& r) : repo(r) {
    doctors = repo.loadDoctors();
    patients = repo.loadPatients();
}

const std::vector<Doctor>& Service::getDoctors() const { return doctors; }
const std::vector<Patient>& Service::getPatients() const { return patients; }

std::vector<Patient> Service::getPatientsForDoctor(const Doctor& doc, bool onlyMine) const {
    std::vector<Patient> result;
    for (const auto& p : patients) {
        if (onlyMine) {
            if (p.getCurrentDoctor() == doc.getName())
                result.push_back(p);
        } else {
            if (p.getNeededSpecialisation() == doc.getSpecialisation() || p.getDiagnosis() == "undiagnosed")
                result.push_back(p);
        }
    }
    std::sort(result.begin(), result.end(), [](const Patient& a, const Patient& b) {
        return a.getAdmissionDate() < b.getAdmissionDate();
    });
    return result;
}

void Service::addPatient(const Patient& p) {
    // Validate name
    if (p.getName().empty()) throw std::runtime_error("Patient name cannot be empty.");
    // Validate date (not in the past)
    std::tm tm = {};
    std::istringstream ss(p.getAdmissionDate());
    ss >> std::get_time(&tm, "%Y-%m-%d");
    std::time_t now = std::time(nullptr);
    if (std::mktime(&tm) < now - 24*60*60) throw std::runtime_error("Admission date is in the past.");
    patients.push_back(p);
    notify();
}

void Service::updatePatient(const std::string& name, const std::string& newDiag, const std::string& newSpec, const std::string& doctorName) {
    std::string normName = normalize(name);
    for (auto& p : patients) {
        if (normalize(p.getName()) == normName) {
            if (p.getDiagnosis() == "undiagnosed" || p.getCurrentDoctor() == doctorName) {
                if (newDiag == "undiagnosed") throw std::runtime_error("Diagnosis cannot be 'undiagnosed'.");
                p.setDiagnosis(newDiag);
                if (p.getNeededSpecialisation() != newSpec) {
                    p.setNeededSpecialisation(newSpec);
                    // Move to new doctor
                    for (const auto& d : doctors) {
                        if (d.getSpecialisation() == newSpec) {
                            p.setCurrentDoctor(d.getName());
                            break;
                        }
                    }
                }
                notify();
                return;
            }
        }
    }
    throw std::runtime_error("Patient not found or not allowed to update.");
}

void Service::save() { repo.savePatients(patients); }

void Service::addObserver(Observer* obs) { observers.push_back(obs); }
void Service::removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
void Service::notify() {
    for (auto obs : observers) obs->update();
}