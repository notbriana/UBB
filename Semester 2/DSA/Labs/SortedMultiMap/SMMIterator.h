#pragma once

#include "SortedMultiMap.h"
#include <vector>

class SMMIterator {
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map); //BC = WC = TC = Θ(m)

	vector<TElem> elements;
	int currentPosition;

	void buildElementsList(); //BC = WC = TC = Θ(m)

public:
	void first(); // BC = WC = TC = Θ(1)
	void next(); //BC = WC = TC = Θ(1)
	bool valid() const; //BC = WC = TC = Θ(1)
	TElem getCurrent() const; //BC = WC = TC = Θ(1)
};
