#include <string>
#include "Departments.h"

string HospitalDepartment::toString() {
	std::string stringHospital = "Name: " + hospitalName + "\nNumber of doctors: " + to_string(numberOfDoctors) + "\n";
	return stringHospital;
}

string NeonantalUnit::toString() {
	return "Type: Neonantal Unit\n" + HospitalDepartment::toString() + "Average grade: " + to_string(averageGrade) + "\nNumber of newborns: " + to_string(numberOfNewborns) + "\nNumber of mothers: " + to_string(numberOfMothers) + "\n";
}

string Surgery::toString()
{
	return "Type: Surgery\n" + HospitalDepartment::toString() + "Number of patients: " + to_string(numberOfPatients) + "\n";
}

bool NeonantalUnit::isEfficient()
{
	return averageGrade > 8.5 && numberOfMothers >= numberOfNewborns;
}

bool Surgery::isEfficient()
{
	double ratio = (double)numberOfPatients / (double)numberOfDoctors;
	return ratio >= 2;
}