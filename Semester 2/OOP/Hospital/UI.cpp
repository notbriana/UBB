#include "UI.h"
#include <string>
#include <iostream>
using namespace std;


void UI::run()
{
	int option;
	while (1)
	{
		cout << "1)Add \n2)Show all \n3)Show efficient \n 4)Write to file \n";
		cin >> option;
		if (option == 1)
			this->addDepartment();
		if (option == 2)
			this->showAll();
		if (option == 3)
			this->showAllEfficient();
		if (option == 4)
			this->writeToFile();
	}
}

void UI::addDepartment()
{
	int option;
	string hospitalName;
	int numberOfDoctors;
	cout << "1 - Neonantal \n 2 - Surgery \n";
	cin >> option;
	cout << "Name: \n";
	cin >> hospitalName;
	cout << "Number doctors : \n";
	cin >> numberOfDoctors;
	if (option == 1)
	{
		double averageGrade;
		int numberOfMothers, numberOfNewborns;
		cout << "Enter the averageGrade: \n";
		cin >> averageGrade;
		cout << "Enter the numberOfMothers: \n";
		cin >> numberOfMothers;
		cout << "Enter the numberOfNewborns: \n";
		cin >> numberOfNewborns;

		this->appController.addDepartment(new NeonantalUnit(hospitalName, numberOfDoctors, averageGrade
			, numberOfMothers, numberOfNewborns));
	}
	else if (option == 2) {
		int numberOfPacients;
		cout << "Enter the numberOfPacients: \n";
		cin >> numberOfPacients;
		this->appController.addDepartment(new Surgery(hospitalName, numberOfDoctors, numberOfPacients));
	}
	else {
		cout << "INVALID";
		return;
	}
}

void UI::showAll() {
	vector<HospitalDepartment*> departments = this->appController.getAll();
	for (auto department : departments)
		cout << department->toString() << "\n";
}

void UI::showAllEfficient() {
	vector<HospitalDepartment*> departments = this->appController.getAllEfficient();
	for (auto department : departments)
		cout << department->toString() << '\n';
}

void UI::writeToFile() {
	string filename;
	cout << "FileName\n";
	cin >> filename;
	this->appController.writeToFile(filename);
}