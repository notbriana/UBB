#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	currentPos = 0;
	currentNode = nullptr;
	currentFreq = 0;

	first();
}

void BagIterator::first() {
	currentPos = 0;
	currentNode = nullptr;
	currentFreq = 0;

	while (currentPos < bag.capacity && bag.table[currentPos] == nullptr) {
		currentPos++;
	}

	if (currentPos < bag.capacity) {
		currentNode = bag.table[currentPos];
		currentFreq = 1;
	}
}

void BagIterator::next() {
	if (!valid()) {
		throw exception();
	}

	if (currentFreq < currentNode->frequency) {
		currentFreq++;
		return;
	}

	currentNode = currentNode->next;
	currentFreq = 1;

	if (currentNode == nullptr) {
		currentPos++;
		while (currentPos < bag.capacity && bag.table[currentPos] == nullptr) {
			currentPos++;
		}

		if (currentPos < bag.capacity) {
			currentNode = bag.table[currentPos];
			currentFreq = 1;
		}
	}
}

bool BagIterator::valid() const {
	return currentNode != nullptr;
}

TElem BagIterator::getCurrent() const
{
	if (!valid()) {
		throw exception();
	}

	return currentNode->element;
}
