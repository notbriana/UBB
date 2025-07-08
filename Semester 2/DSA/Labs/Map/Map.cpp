#include "Map.h"
#include "MapIterator.h"
#include <exception>

Map::Map() {
    capacity = 10;
    nodes = new Node[capacity];
    head = -1;
    tail = -1;
    firstEmpty = 0;
    sizeMap = 0;

    for (int i = 0; i < capacity - 1; i++) {
        nodes[i].next = i + 1;
        nodes[i].prev = -1;
    }
    nodes[capacity - 1].next = -1;
    nodes[capacity - 1].prev = -1;
}

Map::~Map() {
    delete[] nodes;
}

void Map::resize() {
    int newCapacity = capacity * 2;
    Node* newNodes = new Node[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newNodes[i] = nodes[i];
    }

    for (int i = capacity; i < newCapacity - 1; i++) {
        newNodes[i].next = i + 1;
        newNodes[i].prev = -1;
    }
    newNodes[newCapacity - 1].next = -1;
    newNodes[newCapacity - 1].prev = -1;

    firstEmpty = capacity;
    capacity = newCapacity;
    delete[] nodes;
    nodes = newNodes;
}

TValue Map::add(TKey c, TValue v) {
    int current = head;
    while (current != -1) {
        if (nodes[current].data.first == c) {
            TValue oldValue = nodes[current].data.second;
            nodes[current].data.second = v;
            return oldValue;
        }
        current = nodes[current].next;
    }

    if (firstEmpty == -1) {
        resize();
    }

    int newNode = firstEmpty;
    firstEmpty = nodes[firstEmpty].next;

    nodes[newNode].data = std::make_pair(c, v);
    nodes[newNode].next = -1;
    nodes[newNode].prev = tail;

    if (tail != -1) {
        nodes[tail].next = newNode;
    }
    else {
        head = newNode;
    }

    tail = newNode;
    sizeMap++;
    return NULL_TVALUE;
}

TValue Map::search(TKey c) const {
    int current = head;
    while (current != -1) {
        if (nodes[current].data.first == c) {
            return nodes[current].data.second;
        }
        current = nodes[current].next;
    }
    return NULL_TVALUE;
}

TValue Map::remove(TKey c) {
    int current = head;
    while (current != -1) {
        if (nodes[current].data.first == c) {
            TValue oldValue = nodes[current].data.second;

            if (nodes[current].prev != -1) {
                nodes[nodes[current].prev].next = nodes[current].next;
            }
            else {
                head = nodes[current].next;
            }

            if (nodes[current].next != -1) {
                nodes[nodes[current].next].prev = nodes[current].prev;
            }
            else {
                tail = nodes[current].prev;
            }

            nodes[current].next = firstEmpty;
            firstEmpty = current;
            sizeMap--;
            return oldValue;
        }
        current = nodes[current].next;
    }
    return NULL_TVALUE;
}

int Map::size() const {
    return sizeMap;
}

bool Map::isEmpty() const {
    return sizeMap == 0;
}

MapIterator Map::iterator() {
    return MapIterator(*this);
}
