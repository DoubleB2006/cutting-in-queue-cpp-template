#include "../src/JobQueue.hpp"

int main()
{
    JobQueue jq;
    jq.insert(Job("This is job a", 5));
    jq.insert(Job("This is job b", 2));
    jq.insert(Job("This is job c", 9));
    jq.insert(Job("This is job d", 8));
    jq.insert(Job("This is job e", 1));

    jq.runHighestPriority(); // c
    jq.runHighestPriority(); // d
    jq.runHighestPriority(); // a
    jq.runHighestPriority(); // b
    jq.runHighestPriority(); // e
}
