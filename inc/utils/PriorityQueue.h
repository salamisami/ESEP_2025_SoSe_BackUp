#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <iostream>

class MinHeapComparator {
public:
    bool operator()(int a, int b) {
        return a > b; // For min-heap, the smaller element has higher priority
    }
};

class PriorityQueue {
public:
    // Constructor
    PriorityQueue();

    // Add an element to the priority queue
    void enqueue(int value);

    // Remove and return the highest priority element
    int dequeue();

    // Check if the priority queue is empty
    bool isEmpty() const;

    // Get the size of the priority queue
    size_t size() const;

private:
    std::priority_queue<int, std::vector<int>, MinHeapComparator> pq; // Min-heap
};

#endif // PRIORITY_QUEUE_H
