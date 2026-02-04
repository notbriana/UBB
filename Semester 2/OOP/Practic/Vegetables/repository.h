#pragma once
#include<vector>
#include<sstream>
#include<fstream>
#include "vegetables.h"
//using namespace std;

class Repository
{
private:
	std::vector<Vegetables> allVegetables;
public:
	Repository();
	void loadFromFile();
	std::vector <Vegetables> getAllVegetables() { return allVegetables; }
};
