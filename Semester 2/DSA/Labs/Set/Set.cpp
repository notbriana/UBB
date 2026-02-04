#include "Set.h"
#include "SetIterator.h"

Set::Set() : minElement(0), maxElement(0), capacity(10), length(0) {
    elements = new bool[capacity]();
}

Set::Set(const Set& other) : minElement(other.minElement), maxElement(other.maxElement), capacity(other.capacity), length(other.length) {
    elements = new bool[capacity];
    for (int i = 0; i < capacity; i++) {
        elements[i] = other.elements[i];
    }
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        delete[] elements;
        minElement = other.minElement;
        maxElement = other.maxElement;
        capacity = other.capacity;
        length = other.length;
        elements = new bool[capacity];
        for (int i = 0; i < capacity; i++) {
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

void Set::resize(int newMin, int newMax) {
    int newCapacity = newMax - newMin + 1;
    bool* newElements = new bool[newCapacity]();

    for (int i = minElement; i <= maxElement; i++) {
        if (elements[i - minElement]) {
            newElements[i - newMin] = true;
        }
    }

    delete[] elements;
    elements = newElements;
    minElement = newMin;
    maxElement = newMax;
    capacity = newCapacity;
}

bool Set::add(TElem e) {
    if (length == 0) { 
        minElement = maxElement = e;
        capacity = 1;
        elements = new bool[1]();
        elements[0] = true;
        length = 1;
        return true;
    }

    if (e < minElement) {
        resize(e, maxElement);
    }
    else if (e > maxElement) {
        resize(minElement, e);
    }

    if (!elements[e - minElement]) {
        elements[e - minElement] = true;
        length++;
        return true;
    }
    return false;
}

bool Set::remove(TElem e) {
    if (e < minElement || e > maxElement || !elements[e - minElement]) {
        return false;
    }
    elements[e - minElement] = false;
    length--;
    return true;
}

bool Set::search(TElem e) const {
    if (e < minElement || e > maxElement) {
        return false;
    }
    return elements[e - minElement];
}

int Set::difference(const Set& s) {
    int removedCount = 0;
    for (int i = 0; i < capacity; ++i) {
        if (elements[i] && s.search(i + minElement)) {
            elements[i] = false;
            removedCount++;
        }
    }
    return removedCount;
}


int Set::size() const {
    return length;
}

bool Set::isEmpty() const {
    return length == 0;
}

Set::~Set() {
    delete[] elements;
}

SetIterator Set::iterator() const {
    return SetIterator(*this);
}
