#include <fstream>
#include "Controller.h"

void Controller::addDepartment(HospitalDepartment* department) {
	this->departments.push_back(department);
}

vector<HospitalDepartment*> Controller::getAll() {
	return this->departments;
}

vector<HospitalDepartment*> Controller::getAllEfficient() {
	vector<HospitalDepartment*> efficientDepartments;
	for (auto department : this->departments)
	{
		if (department->isEfficient())
			efficientDepartments.push_back(department);
	}
	return efficientDepartments;
}

void Controller::writeToFile(std::string filename) {
	ofstream fin(filename);
	for (auto department : this->departments) {
		fin << department->toString() << "\n";
	}
}