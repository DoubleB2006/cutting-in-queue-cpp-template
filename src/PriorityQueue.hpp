#pragma once
#include "MaxHeap.hpp"

template <class T, class Compare>
class PriorityQueue
{
private:
    MaxHeap<T, Compare> heap;

public:
    bool empty() const { return heap.empty(); }
    std::size_t size() const { return heap.size(); }
    const T& top() const { return heap.top(); }

    void push(const T& value) { heap.push(value); }
    void pop() { heap.pop(); }
};
