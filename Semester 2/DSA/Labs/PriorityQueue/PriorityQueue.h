#pragma once
#include <utility>
#include <stdexcept>

using namespace std;

// DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

struct Node {
    Element data;
    Node* next;
};

class PriorityQueue {
private:
    Node* head;
    Relation relation;

public:
    // implicit constructor
    PriorityQueue(Relation r); //Θ(1) = BC = WC = TC

    // pushes an element with priority to the queue
    void push(TElem e, TPriority p); //BC = Θ(1) WC = Θ(n) TC = O(n)!!

    // returns the element with the highest priority with respect to the order relation
    // throws exception if the queue is empty
    Element top() const; //BC = WC = TC = Θ(1)


    // removes and returns the element with the highest priority
    // throws exception if the queue is empty
    Element pop(); //BC = WC = TC = Θ(1)


    // checks if the queue is empty
    bool isEmpty() const; //BC = WC = TC = Θ(1)


    void merge(PriorityQueue& pq); // BC = Θ(n)  WC = Θ(n*m) TC = O(n*m)!!!

    // destructor
    ~PriorityQueue(); //BC = WC = TC = Θ(n)

};
