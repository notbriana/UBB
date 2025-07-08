#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

struct BSTNode {
    TKey key;
    TValue* values;    
    int valuesCount;   
    int capacity;      
    BSTNode* left;
    BSTNode* right;

    BSTNode(TKey k, TValue v) : key(k), valuesCount(1), capacity(2), left(nullptr), right(nullptr) {
        values = new TValue[capacity];
        values[0] = v;
    } 

    ~BSTNode() {
        delete[] values;
    }
};

class SortedMultiMap {
    friend class SMMIterator;
private:
    BSTNode* root;
    Relation rel;
    int mapSize;

    BSTNode* insertNode(BSTNode* node, TKey key, TValue value); //BC = Θ(1) WC = Θ(n + m) TC = O(n + m)
    BSTNode* removeNode(BSTNode* node, TKey key, TValue value, bool& removed); //BC = Θ(m) WC = Θ(n + m) TC = O(n + m)
    BSTNode* findMin(BSTNode* node); //BC = Θ(1) WC = Θ(h) TC = O(h)
    void destroyTree(BSTNode* node); //BC = WC = TC = Θ(n)
    void addValueToNode(BSTNode* node, TValue value); //BC = Θ(1) WC = Θ(m) TC = O(m)
    bool removeValueFromNode(BSTNode* node, TValue value); //BC = WC = TC = Θ(m)
    void collectInOrder(BSTNode* node, vector<TElem>& elements) const; //BC = WC = TC = Θ(n*m)

public:

    // constructor
    SortedMultiMap(Relation r);// BC = WC = TC = Θ(1)

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v); //BC = Θ(1) WC = Θ(n) TC = O(n)

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const; //BC = Θ(m) WC = Θ(n + m) TC = O(n + m)

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);//BC = Θ(m) WC = Θ(n + m) TC = O(n + m)

    //returns the number of key-value pairs from the sorted multimap
    int size() const; // BC = WC = TC = Θ(1)

    //verifies if the sorted multi map is empty
    bool isEmpty() const; //BC = WC = TC = Θ(1)

    // returns an iterator for the sorted multimap. The iterator will return the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const; //BC = WC = TC = Θ(n * m)

    // destructor
    ~SortedMultiMap(); //BC = WC = TC = Θ(n)

    int addIfNotPresent(SortedMultiMap& smm); //BC = Θ(p * m) WC = Θ(p * (n + m)) TC = O(p * (n + m)) ;p =pairs in smm, m - keys in smm, n - keys in current

};
