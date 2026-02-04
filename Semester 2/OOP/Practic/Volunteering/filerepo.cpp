#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& df, const std::string& vf) : deptFile(df), volFile(vf) {}

std::vector<Department> FileRepo::loadDepartments() {
    std::vector<Department> depts;
    std::ifstream fin(deptFile);
    std::string line;
    while (getline(fin, line)) {
        std::string name = line;
        if (!getline(fin, line)) break;
        std::string desc = line;
        depts.emplace_back(name, desc);
    }
    return depts;
}

std::vector<Volunteer> FileRepo::loadVolunteers() {
    std::vector<Volunteer> vols;
    std::ifstream fin(volFile);
    std::string line;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, email, interestsStr, dept;
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, interestsStr, '|');
        getline(ss, dept, '|');
        std::vector<std::string> interests;
        std::stringstream iss(interestsStr);
        std::string interest;
        while (getline(iss, interest, ',')) interests.push_back(interest);
        vols.emplace_back(name, email, interests, dept);
    }
    return vols;
}

void FileRepo::saveVolunteers(const std::vector<Volunteer>& volunteers) {
    std::ofstream fout(volFile);
    for (const auto& v : volunteers) {
        fout << v.getName() << "|" << v.getEmail() << "|";
        for (size_t i = 0; i < v.getInterests().size(); ++i) {
            fout << v.getInterests()[i];
            if (i + 1 < v.getInterests().size()) fout << ",";
        }
        fout << "|" << v.getDepartment() << "\n";
    }
}