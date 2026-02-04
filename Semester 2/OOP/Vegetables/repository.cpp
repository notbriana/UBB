#include "repository.h"

Repository::Repository() {
	loadFromFile();
}

void Repository::loadFromFile() {
	std::ifstream file("vegetables.txt");
	std::string line;
	std::string family, name, list;
	const char del = '|';
	while (getline(file, line)) {
		std::istringstream iss(line);
		getline(iss, family, del);
		getline(iss, name, del);
		getline(iss, list, del);
		allVegetables.push_back(Vegetables(family, name, list));
	}
}