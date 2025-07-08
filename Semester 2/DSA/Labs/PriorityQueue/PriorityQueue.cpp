#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(Relation r) {
    this->head = nullptr;
    this->relation = r;
}

void PriorityQueue::push(TElem e, TPriority p) {
    Node* newNode = new Node{ std::make_pair(e, p), nullptr };
    if (this->head == nullptr || this->relation(p, this->head->data.second)) {
        newNode->next = this->head;
        this->head = newNode;
    }
    else {
        Node* current = this->head;
        while (current->next != nullptr && !this->relation(p, current->next->data.second)) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Element PriorityQueue::top() const {
    if (this->isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return this->head->data;
}

Element PriorityQueue::pop() {
    if (this->isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    Node* nodeToRemove = this->head;
    Element topElement = nodeToRemove->data;
    this->head = this->head->next;
    delete nodeToRemove;
    return topElement;
}

bool PriorityQueue::isEmpty() const {
    return this->head == nullptr;
}

void PriorityQueue::merge(PriorityQueue& pq) {
    while (!pq.isEmpty()) {
        Element data = pq.pop();
        this->push(data.first, data.second);
    }
}


PriorityQueue::~PriorityQueue() {
    while (!this->isEmpty()) {
        this->pop();
    }
}
