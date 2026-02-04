#pragma once

#include "Buildings.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include < algorithm>

using namespace std;

class Controller {
	vector<Building*> Buildings;
public:
	Controller() {
		Building* house1 = new House("str asda", 2202, "casa", true);
		Building* house2 = new House("str 2da3a", 2012, "casa", true);

		Building* flat1 = new Block("str dwa", 2022, 22, 23);
		Building* flat2 = new Block("str aaaa", 2105, 5, 10);

		Buildings.push_back(flat1);
		Buildings.push_back(flat2);
		Buildings.push_back(house1);
		Buildings.push_back(house2);
	}
	~Controller() {
		for (auto building : Buildings)
			delete building;
	};
	void addBuilding(Building* a);
	vector<Building*> getAll() { return this->Buildings; }
	bool adressAlready(string addressGiven) {
		for (auto building : Buildings) {
			if (building->address == addressGiven) return true;
		}
		return false;
	}
	vector<Building*> getAllSorted() {
		vector<Building*> all = getAll();
		sort(all.begin(), all.end(), [](Building* a, Building* b) {
			return a->constructionYear < b->constructionYear;
			});
		return all;
	}
	void writeToFileRestored(string file);
	void writeToFileDemolished(string file);

};