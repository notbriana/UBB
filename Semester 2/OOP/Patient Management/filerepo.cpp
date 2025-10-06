#include "filerepo.h"
#include <fstream>
#include <sstream>

std::vector<Doctor> FileRepo::loadDoctors() {
    std::vector<Doctor> doctors;
    std::ifstream fin(doctorsFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, spec;
        getline(iss, name, ',');
        getline(iss, spec, ',');
        if (!name.empty() && !spec.empty())
            doctors.emplace_back(name, spec);
    }
    return doctors;
}

std::vector<Patient> FileRepo::loadPatients() {
    std::vector<Patient> patients;
    std::ifstream fin(patientsFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, diag, spec, doc, date;
        getline(iss, name, ',');
        getline(iss, diag, ',');
        getline(iss, spec, ',');
        getline(iss, doc, ',');
        getline(iss, date, ',');
        if (!name.empty())
            patients.emplace_back(name, diag, spec, doc, date);
    }
    return patients;
}

void FileRepo::savePatients(const std::vector<Patient>& patients) {
    std::ofstream fout(patientsFile);
    for (const auto& p : patients) {
        fout << p.getName() << "," << p.getDiagnosis() << "," << p.getNeededSpecialisation()
             << "," << p.getCurrentDoctor() << "," << p.getAdmissionDate() << "\n";
    }
}