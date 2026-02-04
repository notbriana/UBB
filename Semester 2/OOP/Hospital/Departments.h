#pragma once

#include <string>

using namespace std;

class Departments {

};

class HospitalDepartment
{
protected:
	string hospitalName;
	int numberOfDoctors;


public:

	HospitalDepartment() : hospitalName{ "" }, numberOfDoctors{ 0 } {};
	HospitalDepartment(string hospitalName, int numberOfDoctors) : hospitalName{ hospitalName }, numberOfDoctors{ numberOfDoctors } {};
	virtual bool isEfficient() { return false; }
	virtual string toString();
	string getName(){ return this->hospitalName; }
};

class NeonantalUnit : public HospitalDepartment {
public:

	double averageGrade;
	int  numberOfMothers, numberOfNewborns;
	NeonantalUnit(string hospitalName, int numberOfDoctors, double averageGrade, int numberOfMothers, int numberOfNewborns) :
		HospitalDepartment{ hospitalName, numberOfDoctors }, averageGrade{ averageGrade }, numberOfMothers{ numberOfMothers }, numberOfNewborns{ numberOfNewborns } {
	};
	bool isEfficient();
	string toString();
};

class Surgery : public HospitalDepartment {
private:
	int numberOfPatients;
public:

	Surgery(string hospitalName, int numberOfDoctors, int numberOfPatients) :
		HospitalDepartment{ hospitalName, numberOfDoctors }, numberOfPatients{ numberOfPatients }{
	};
	bool isEfficient();
	string toString();
};