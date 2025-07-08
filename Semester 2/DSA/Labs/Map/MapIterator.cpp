#include "MapIterator.h"
#include <exception>

MapIterator::MapIterator(Map& m) : map(m) {
    first();
}

void MapIterator::first() {
    current = map.head;
}

void MapIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    current = map.nodes[current].next;
}

TElem MapIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return map.nodes[current].data;
}

bool MapIterator::valid() const {
    return current != -1;
}

TElem MapIterator::remove() {
    if (!valid()) {
        throw std::exception("Invalid iterator!");
    }

    TElem removedElement = map.nodes[current].data;

    int nextNode = map.nodes[current].next;
    map.remove(removedElement.first);

    current = nextNode;

    return removedElement;
}
