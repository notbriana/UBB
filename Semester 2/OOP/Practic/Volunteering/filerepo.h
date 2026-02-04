#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string deptFile, volFile;
public:
    FileRepo(const std::string& df, const std::string& vf);
    std::vector<Department> loadDepartments();
    std::vector<Volunteer> loadVolunteers();
    void saveVolunteers(const std::vector<Volunteer>& volunteers);
};