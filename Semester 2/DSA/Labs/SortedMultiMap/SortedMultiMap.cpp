#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) : root(nullptr), rel(r), mapSize(0) {
}

void SortedMultiMap::add(TKey c, TValue v) {
    root = insertNode(root, c, v);
    mapSize++;
}

BSTNode* SortedMultiMap::insertNode(BSTNode* node, TKey key, TValue value) {
    if (node == nullptr) {
        return new BSTNode(key, value);
    }

    if (key == node->key) {
        addValueToNode(node, value);
        mapSize--; 
        return node;
    }

    if (rel(key, node->key) && key != node->key) {
        node->left = insertNode(node->left, key, value);
    }
    else {
        node->right = insertNode(node->right, key, value);
    }

    return node;
}

void SortedMultiMap::addValueToNode(BSTNode* node, TValue value) {
    if (node->valuesCount == node->capacity) {
        int newCapacity = node->capacity * 2;
        TValue* newValues = new TValue[newCapacity];
        for (int i = 0; i < node->valuesCount; i++) {
            newValues[i] = node->values[i];
        }
        delete[] node->values;
        node->values = newValues;
        node->capacity = newCapacity;
    }

    node->values[node->valuesCount] = value;
    node->valuesCount++;
    mapSize++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> result;
    BSTNode* current = root;

    while (current != nullptr) {
        if (c == current->key) {
            for (int i = 0; i < current->valuesCount; i++) {
                result.push_back(current->values[i]);
            }
            break;
        }
        else if (rel(c, current->key) && c != current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return result;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    bool removed = false;
    root = removeNode(root, c, v, removed);
    if (removed) {
        mapSize--;
    }
    return removed;
}

BSTNode* SortedMultiMap::removeNode(BSTNode* node, TKey key, TValue value, bool& removed) {
    if (node == nullptr) {
        removed = false;
        return nullptr;
    }

    if (key == node->key) {
        if (removeValueFromNode(node, value)) {
            removed = true;
            if (node->valuesCount == 0) {
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    return nullptr;
                }
                else if (node->left == nullptr) {
                    BSTNode* temp = node->right;
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr) {
                    BSTNode* temp = node->left;
                    delete node;
                    return temp;
                }
                else {
                    BSTNode* minRight = findMin(node->right);
                    node->key = minRight->key;

                    delete[] node->values;
                    node->values = new TValue[minRight->capacity];
                    node->capacity = minRight->capacity;
                    node->valuesCount = minRight->valuesCount;
                    for (int i = 0; i < minRight->valuesCount; i++) {
                        node->values[i] = minRight->values[i];
                    }

                    bool tempRemoved = false;
                    node->right = removeNode(node->right, minRight->key, minRight->values[0], tempRemoved);

                    mapSize += node->valuesCount - 1;
                }
            }
        }
        else {
            removed = false;
        }
        return node;
    }
    else if (rel(key, node->key) && key != node->key) {
        node->left = removeNode(node->left, key, value, removed);
        return node;
    }
    else {
        node->right = removeNode(node->right, key, value, removed);
        return node;
    }
}

bool SortedMultiMap::removeValueFromNode(BSTNode* node, TValue value) {
    for (int i = 0; i < node->valuesCount; i++) {
        if (node->values[i] == value) {
            for (int j = i; j < node->valuesCount - 1; j++) {
                node->values[j] = node->values[j + 1];
            }
            node->valuesCount--;
            return true;
        }
    }
    return false;
}

BSTNode* SortedMultiMap::findMin(BSTNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

int SortedMultiMap::size() const {
    return mapSize;
}

bool SortedMultiMap::isEmpty() const {
    return mapSize == 0;
}

void SortedMultiMap::collectInOrder(BSTNode* node, vector<TElem>& elements) const {
    if (node == nullptr) return;

    collectInOrder(node->left, elements);

    for (int i = 0; i < node->valuesCount; i++) {
        elements.push_back(make_pair(node->key, node->values[i]));
    }

    collectInOrder(node->right, elements);
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

void SortedMultiMap::destroyTree(BSTNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

SortedMultiMap::~SortedMultiMap() {
    destroyTree(root);
}

int SortedMultiMap::addIfNotPresent(SortedMultiMap& smm) {
    int added = 0;
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()) {
        TKey key = it.getCurrent().first;
        TValue value = it.getCurrent().second;
        if (this->search(key).empty()) {
            this->add(key, value);
            ++added;
        }
        it.next();
    }
    return added;
}
