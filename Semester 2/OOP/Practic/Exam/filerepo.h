#pragma once
#include "domain.h"
#include <vector>

class FileRepo {
	std::string departmentFile, volunteerFile;
public:
	FileRepo(const std::string& dF, const std::string& vF);
	std::vector<Department> loadDepartments();
	std::vector<Volunteer> loadVolunteers();
	void saveVolunteers(const std::vector<Volunteer>& volunteers);
};