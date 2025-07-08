#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator;
class Bag {

private:
	// Representation for hash table with separate chaining
	// Each position in the hash table contains a linked list of <element, frequency> pairs

	// Node structure for the linked list
	struct Node {
		TElem element;
		int frequency;
		Node* next;

		Node(TElem e, int f) : element(e), frequency(f), next(nullptr) {}
	};

	Node** table;  
	int capacity;  
	int totalSize; 
	int uniqueSize;

	const double MAX_LOAD_FACTOR = 0.7;

	int hash(TElem e) const {
		// Using a simple hash function for integers
		// Ensure positive values and modulo by capacity
		return (e % capacity + capacity) % capacity;
	}

	// Resize the hash table when load factor is exceeded
	void resize(); // BC = Θ(n) WC = Θ(n) TC = Θ(n)

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag(); //BC = Θ(n) WC = Θ(n) TC = Θ(n)

	//adds an element to the bag
	void add(TElem e); //BC = Θ(1) WC = Θ(n) TC = O(n)

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e); //BC = Θ(1) WC = Θ(n) TC = O(n)

	//checks if an element appearch is the bag
	bool search(TElem e) const; //BC = Θ(1) WC = Θ(n) TC = O(n)

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const; //BC = Θ(1) WC = Θ(n) TC = O(n)

	//returns the number of elements from the bag
	int size() const; //BC = Θ(1) WC = Θ(1) TC = Θ(1)

	//returns an iterator for this bag
	BagIterator iterator() const; //BC = Θ(1) WC = Θ(1) TC = Θ(1)

	//checks if the bag is empty
	bool isEmpty() const; //BC = Θ(1) WC = Θ(1) TC = Θ(1)

	//destructor
	~Bag(); //BC = Θ(n) WC = Θ(n) TC = Θ(n)

	TElem mostFrequent() const; //BC = Θ(n) WC = Θ(n) TC = Θ(n) 
};
