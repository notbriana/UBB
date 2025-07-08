#pragma once
#include <utility>
//DO NOT INCLUDE MAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)
class MapIterator;

struct Node {
    TElem data;
    int next;
    int prev;
};

class Map {
    //DO NOT CHANGE THIS PART
    friend class MapIterator;

private:
    Node* nodes;
    int capacity;
    int head;
    int tail;
    int firstEmpty;
    int sizeMap;

    void resize(); //BC = WC = TC = Θ(n)

public:
    // implicit constructor
    Map(); //BC = WC = TC = Θ(1)

    // adds a pair (key,value) to the map
    //if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
    //if the key does not exist, a new pair is added and the value null is returned
    TValue add(TKey c, TValue v); //BC =  Θ(1) WC = Θ(n)  TC = O(n)

    //searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
    TValue search(TKey c) const; //BC =  Θ(1) WC = Θ(n)  TC = O(n)

    //removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
    TValue remove(TKey c); //BC =  Θ(1) WC = Θ(n)  TC = O(n)

    //returns the number of pairs (key,value) from the map
    int size() const; //BC = WC = TC = Θ(1)

    //checks whether the map is empty or not
    bool isEmpty() const; //BC = WC = TC = Θ(1)

    //returns an iterator for the map
    MapIterator iterator(); //BC = WC = TC = Θ(1)

    // destructor
    ~Map(); //BC = WC = TC = Θ(1)
};
