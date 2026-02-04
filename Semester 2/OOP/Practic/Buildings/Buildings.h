#pragma once
#include <iostream>
#include <string>

using namespace std;

class Building {
public:
	string address;
	int constructionYear;

	Building(string address, int constructionYear) : address{ address }, constructionYear{ constructionYear } {};
	virtual bool mustBeRestored() { return false; }
	virtual bool canBeDemolished() { return false; }
	virtual string toString();
};

class Block : public Building {
private:
	int totalAp;
	int occupiedAp;
public:
	Block(string address, int constructionYear, int totalAp, int occupiedAp) : Building{ address, constructionYear }, totalAp{ totalAp }, occupiedAp{ occupiedAp } {};
	bool mustBeRestored();
	bool canBeDemolished();
	string toString();
};

class House : public Building {
private:
	string type;
	bool isHistorical;
public:
	House(string address, int constructionYear, string type, bool isHistorical) : Building{ address, constructionYear }, type{ type }, isHistorical{ isHistorical } {};
	bool mustBeRestored();
	bool canBeDemolished();
	string toString();
};