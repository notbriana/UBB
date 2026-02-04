
#pragma once
#include "repository.h"
#include<vector>
#include<string>
#include<algorithm>

//using namespace std;

class Service
{
private:
	Repository repository;

public:
	std::vector<Vegetables> getAllVegetables();
	std::vector<std::string> getAllUniqueFamilies();
	std::vector<Vegetables> getAllVegetablesBelongingToFamily(std::string family);
	Vegetables getVegetableFromName(std::string name);
};
