#include "filerepo.h"
#include <iomanip>
#include <sstream>
#include <fstream>


FileRepo::FileRepo(const std::string& dF, const std::string& vF): departmentFile(dF), volunteerFile(vF){}


std::vector<Department> FileRepo::loadDepartments() {
    std::vector<Department> departments;
    std::ifstream fin(departmentFile);
    std::string line;
    while (getline(fin, line)) {
        std::string name = line;
        if (!getline(fin, line)) break;
        std::string description = line;
        departments.emplace_back(name, description);
    }
    return departments;
}

std::vector<Volunteer> FileRepo::loadVolunteers() {
    std::vector<Volunteer> volunteers;
    std::ifstream fin(volunteerFile);
    std::string line;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, email, interesulttsStr, department;
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, interesulttsStr, '|');
        getline(ss, department, '|');
        std::vector<std::string> interesultts;
        std::stringstream iss(interesulttsStr);
        std::string interesultt;
        while (getline(iss, interesultt, ',')) 
            interesultts.push_back(interesultt);
        volunteers.emplace_back(name, email, interesultts, department);
    }
    return volunteers;
}


void FileRepo::saveVolunteers(const std::vector<Volunteer>& volunteers) {
    std::ofstream fout(volunteerFile);
    for (const auto& v : volunteers) {
        fout << v.getName() << "|" << v.getEmail() << "|";
        for (size_t i = 0; i < v.getInterests().size(); ++i) {
            fout << v.getInterests()[i];
            if (i + 1 < v.getInterests().size()) fout << ",";
        }
        fout << "|" << v.getDepartment() << "\n";
    }
}
