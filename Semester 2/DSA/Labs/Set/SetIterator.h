#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;
private:
	const Set& set;
	int current;
	SetIterator(const Set& s);


public:
	void first(); // Best: O(1), Worst: O(n), Average: O(n)
	void next(); // Best: O(1), Worst: O(n), Average: O(n)
	TElem getCurrent(); // Best: O(1), Worst: O(1), Average: O(1)
	bool valid() const; // Best: O(1), Worst: O(1), Average: O(1)
};


