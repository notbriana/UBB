#include "SetIterator.h"
#include "Set.h"
#include <stdexcept>

SetIterator::SetIterator(const Set& s) : set(s), current(0) {
    while (current < set.capacity && !set.elements[current]) {
        current++;
    }
}

void SetIterator::first() {
    current = 0;
    while (current < set.capacity && !set.elements[current]) {
        current++;
    }
}

void SetIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    current++;
    while (current < set.capacity && !set.elements[current]) {
        current++;
    }
}

TElem SetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return current + set.minElement;
}

bool SetIterator::valid() const {
    return current < set.capacity;
}
