#pragma once
#include<string>
#include<iostream>
#include<fstream>
//using namespace std;

class Vegetables
{
private:
	std::string family, name, list;

public:
	Vegetables(std::string family, std::string name, std::string list) : family(family), name(name), list(list) { ; };
	std::string getFamily() const { return family; }
	std::string getName() const { return name; }
	std::string getList() const { return list; }
	bool operator <(const Vegetables& v) { return family < v.getFamily(); }
	std::string tostd() const { return name + " | " + list; }
};
