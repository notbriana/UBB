#pragma once
#include<iostream>
#include "Service.h"
using namespace std;

class UI
{
public:
	Controller appController;

	void run();
	void addAppliance();
	void showAppliances();
	void showInefficient();
	void saveToFile();
};

