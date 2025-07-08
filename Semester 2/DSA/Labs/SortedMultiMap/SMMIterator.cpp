#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d), currentPosition(0) {
    buildElementsList();
}

void SMMIterator::buildElementsList() {
    elements.clear();
    map.collectInOrder(map.root, elements);
    currentPosition = 0;
}

void SMMIterator::first() {
    currentPosition = 0;
}

void SMMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    currentPosition++;
}

bool SMMIterator::valid() const {
    return currentPosition < elements.size();
}

TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return elements[currentPosition];
}
