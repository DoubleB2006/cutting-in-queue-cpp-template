#pragma once
#include <iostream>
#include "PriorityQueue.hpp"
#include "job.hpp"

// Larger priority number = higher priority
struct JobHigherPriority
{
    bool operator()(Job& a, Job& b) 
    {
        return a.getPriority() < b.getPriority();
    }
};

class JobQueue
{
private:
    PriorityQueue<Job, JobHigherPriority> pq;

public:
    void insert(const Job& job)
    {
        pq.push(job);
    }

    void runHighestPriority()
    {
        if (pq.empty())
        {
            std::cout << "No jobs to run.\n";
            return;
        }
        Job topJob = pq.top();
        pq.pop();
        topJob.execute();
    }
};
