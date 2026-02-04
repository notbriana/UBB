#include "service.h"

std::vector<Vegetables> Service::getAllVegetables() {
	std::vector<Vegetables> all = repository.getAllVegetables();
	sort(all.begin(), all.end());
	return all;
}

std::vector<std::string>  Service::getAllUniqueFamilies() {
	std::ofstream fout("test.txt");

	std::vector<Vegetables> all = repository.getAllVegetables();
	sort(all.begin(), all.end());
	std::vector<std::string> allfinal;

	for (int i = 0; i < all.size(); i++) {
		bool found = 0;
		for (int j = 0; j < allfinal.size(); j++)
			if (all[i].getFamily() == allfinal[j]) found = 1;

		if (!found) {
			allfinal.push_back(all[i].getFamily());
			fout << all[i].tostd();
		}
	}
	return allfinal;
}

std::vector<Vegetables> Service::getAllVegetablesBelongingToFamily(std::string family) {
	std::vector<Vegetables> all = repository.getAllVegetables();
	std::vector<Vegetables> allfinal;

	for (auto x : all)
		if (x.getFamily() == family) allfinal.push_back(x);

	return allfinal;
}

Vegetables Service::getVegetableFromName(std::string name) {
	std::vector<Vegetables> all = repository.getAllVegetables();
	for (auto x : all)
		if (x.getName() == name) return x;
	return Vegetables("none", "none", "None");
}