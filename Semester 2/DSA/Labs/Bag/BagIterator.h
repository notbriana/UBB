#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;

private:
	const Bag& bag;

	int currentPos;      
	Bag::Node* currentNode;
	int currentFreq;     

	BagIterator(const Bag& c); //BC = Θ(1) WC  = Θ(n) TC = O(n)
public:
	void first(); //BC =  Θ(1) WC = Θ(n) TC = O(n)
	void next(); //BC =  Θ(1) WC = Θ(n) TC = O(n)
	TElem getCurrent() const; //BC =  Θ(1) WC = Θ(n) TC = Θ(1)
	bool valid() const; //BC =  Θ(1) WC = Θ(1) TC = Θ(1)
};
