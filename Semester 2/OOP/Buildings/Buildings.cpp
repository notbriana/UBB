#include "Buildings.h"
#include <string>
#include <iostream>

using namespace std;

string Building::toString() {
	return "\nAddress: " + address + "\nConstruction Year: " + to_string(constructionYear) + "\n";
}

string Block::toString()
{
	return "Type: Block \n" + Building::toString() + "Total apartments: " + to_string(totalAp) + "\nOccupied Appartments: " + to_string(occupiedAp) + "\n";
}

string House::toString()
{
	return "Type: House \n" + Building::toString() + "Type: " + type + "\nIs historical: " + to_string(isHistorical) + "\n";
}

bool Block::mustBeRestored()
{
	double percentage = double(occupiedAp) / double(totalAp);
	if (percentage > 0.80 && 2025 - constructionYear >= 40)
		return true;
	return false;
}

bool Block::canBeDemolished() {
	double percentage = double(occupiedAp) / double(totalAp);
	if (percentage <= 0.05)
		return true;
	return false;
}

bool House::mustBeRestored()
{
	if (2025 - constructionYear >= 100)
		return true;
	return false;
}

bool House::canBeDemolished()
{
	if (isHistorical == false)
		return true;
	return false;
}
