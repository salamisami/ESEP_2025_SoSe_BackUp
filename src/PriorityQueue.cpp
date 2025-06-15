#include "PriorityQueue.h"

// Constructor
PriorityQueue::PriorityQueue() {}

// Add an element to the priority queue
void PriorityQueue::enqueue(int value) {
    pq.push(value);
}

// Remove and return the highest priority element
int PriorityQueue::dequeue() {
    if (!pq.empty()) {
        int value = pq.top();
        pq.pop();
        return value;
    } else {
        std::cerr << "Priority queue is empty!" << std::endl;
        return -1; // Indicate that the queue is empty
    }
}

// Check if the priority queue is empty
bool PriorityQueue::isEmpty() const {
    return pq.empty();
}

// Get the size of the priority queue
size_t PriorityQueue::size() const {
    return pq.size();
}<