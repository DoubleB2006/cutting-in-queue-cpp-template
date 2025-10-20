#pragma once
#include <vector>
#include <cstddef>
#include <utility>

template <class T, class Compare>
class MaxHeap
{
private:
    std::vector<T> data;
    Compare comp;

    std::size_t parent(std::size_t i) { return (i - 1) / 2; }
    std::size_t left(std::size_t i)   { return 2 * i + 1; }
    std::size_t right(std::size_t i)  { return 2 * i + 2; }

    void siftUp(std::size_t i)
    {
        while (i > 0)
        {
            std::size_t p = parent(i);
            // if parent is lower priority than child, swap
            if (comp(data[p], data[i]))
            {
                T tmp = data[p];
                data[p] = data[i];
                data[i] = tmp;
                i = p;
            }
            else break;
        }
    }

    void siftDown(std::size_t i)
    {
        std::size_t n = data.size();
        while (true)
        {
            std::size_t l = left(i);
            std::size_t r = right(i);
            std::size_t best = i;

            if (l < n && comp(data[best], data[l])) best = l;
            if (r < n && comp(data[best], data[r])) best = r;

            if (best != i)
            {
                T tmp = data[i];
                data[i] = data[best];
                data[best] = tmp;
                i = best;
            }
            else break;
        }
    }

public:
    bool empty()  { return data.empty(); }
    std::size_t size()  { return data.size(); }
    T& top()  { return data.front(); }

    void push( T& value)
    {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    void pop()
    {
        if (data.empty()) return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
    }
};

