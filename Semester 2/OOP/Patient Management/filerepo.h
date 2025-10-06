#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string doctorsFile, patientsFile;
public:
    FileRepo(const std::string& df, const std::string& pf) : doctorsFile(df), patientsFile(pf) {}
    std::vector<Doctor> loadDoctors();
    std::vector<Patient> loadPatients();
    void savePatients(const std::vector<Patient>& patients);
};