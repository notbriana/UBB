#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	capacity = 16; 
	table = new Node * [capacity];

	for (int i = 0; i < capacity; i++) {
		table[i] = nullptr;
	}

	totalSize = 0;
	uniqueSize = 0;
}

void Bag::add(TElem elem) {
	if ((double)uniqueSize / capacity > MAX_LOAD_FACTOR) {
		resize();
	}

	int hashValue = hash(elem);

	Node* current = table[hashValue];
	while (current != nullptr) {
		if (current->element == elem) {
			current->frequency++;
			totalSize++;
			return;
		}
		current = current->next;
	}

	Node* newNode = new Node(elem, 1);
	newNode->next = table[hashValue];
	table[hashValue] = newNode;

	totalSize++;
	uniqueSize++;
}

bool Bag::remove(TElem elem) {
	int hashValue = hash(elem);

	Node* current = table[hashValue];
	Node* prev = nullptr;

	while (current != nullptr) {
		if (current->element == elem) {
			current->frequency--;
			totalSize--;

			if (current->frequency == 0) {
				if (prev == nullptr) {
					table[hashValue] = current->next;
				}
				else {
					prev->next = current->next;
				}

				delete current;
				uniqueSize--;
			}

			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

bool Bag::search(TElem elem) const {
	int hashValue = hash(elem);

	Node* current = table[hashValue];
	while (current != nullptr) {
		if (current->element == elem) {
			return true;
		}
		current = current->next;
	}

	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	int hashValue = hash(elem);

	Node* current = table[hashValue];
	while (current != nullptr) {
		if (current->element == elem) {
			return current->frequency;
		}
		current = current->next;
	}

	return 0;
}

int Bag::size() const {
	return totalSize;
}

bool Bag::isEmpty() const {
	return totalSize == 0;
}

void Bag::resize() {
	int oldCapacity = capacity;
	Node** oldTable = table;

	capacity *= 2;
	table = new Node * [capacity];

	for (int i = 0; i < capacity; i++) {
		table[i] = nullptr;
	}

	totalSize = 0;
	uniqueSize = 0;

	for (int i = 0; i < oldCapacity; i++) {
		Node* current = oldTable[i];
		while (current != nullptr) {
			Node* next = current->next;

			for (int j = 0; j < current->frequency; j++) {
				add(current->element);
			}

			delete current;

			current = next;
		}
	}

	delete[] oldTable;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

Bag::~Bag() {
	for (int i = 0; i < capacity; i++) {
		Node* current = table[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	delete[] table;
}

TElem Bag::mostFrequent() const {
	if (isEmpty()) {
		return NULL_TELEM;
	}

	TElem result = NULL_TELEM;
	int maxFreq = 0;

	for (int i = 0; i < capacity; ++i) {
		Node* node = table[i];
		while (node != nullptr) {
			if (node->frequency > maxFreq) {
				maxFreq = node->frequency;
				result = node->element;
			}
			node = node->next;
		}
	}
	return result;
}


