#pragma once

#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;

class Set {
    friend class SetIterator;

private:
    bool* elements;
    int minElement;
    int maxElement;
    int capacity;
    int length;

    void resize(int newMin, int newMax); //O(n)

public:
    //implicit constructor
    Set(); // Best: O(1), Worst: O(1), Average: O(1)

    //copy constructor
    Set(const Set& other); // Best: O(n), Worst: O(n), Average: O(n)

    //assignment operator
    Set& operator=(const Set& other); // Best: O(n), Worst: O(n), Average: O(n)

    //adds an element to the set
    bool add(TElem e); // Best: O(1), Worst: O(n), Average: O(1)

    //removes an element from the set
    bool remove(TElem e); // Best: O(1), Worst: O(1), Average: O(1)

    //checks whether an element belongs to the set or not
    bool search(TElem elem) const; // Best: O(1), Worst: O(1), Average: O(1)

    //returns the number of elements;
    int size() const; // Best: O(1), Worst: O(1), Average: O(1)

    //check whether the set is empty or not;
    bool isEmpty() const; // Best: O(1), Worst: O(1), Average: O(1)

    //keeps only the elements that don't appear in current set and returns the number of removed elements
    int difference(const Set& s); // Best: O(n) Worst: O(n) Avarage: O(n)

    //return an iterator for the set
    SetIterator iterator() const; // Best: O(1), Worst: O(1), Average: O(1)

    // destructor
    ~Set(); // Best: O(1), Worst: O(1), Average: O(1)
};
