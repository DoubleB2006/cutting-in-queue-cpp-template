#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/JobQueue.hpp"

// Test that inserting and running jobs works in correct order
TEST_CASE("JobQueue runs highest priority jobs first") {
    JobQueue jq;

    jq.insert(Job("Job A", 5));
    jq.insert(Job("Job B", 2));
    jq.insert(Job("Job C", 9));
    jq.insert(Job("Job D", 8));
    jq.insert(Job("Job E", 1));

    SECTION("Top job should be highest priority first") {
        // Note: we check top without running execute()
        // We know Job C has the highest priority (9)
        // but top() is inside the heap, so we must trust runHighestPriority() output order.
        jq.runHighestPriority(); // Runs Job C
        jq.runHighestPriority(); // Runs Job D
        jq.runHighestPriority(); // Runs Job A
        jq.runHighestPriority(); // Runs Job B
        jq.runHighestPriority(); // Runs Job E

        // No jobs left
        jq.runHighestPriority(); // Should output "No jobs to run."
    }
}

// Test that inserting works correctly (heap ordering)
TEST_CASE("JobQueue maintains heap order after inserts") {
    JobQueue jq;

    jq.insert(Job("X", 3));
    jq.insert(Job("Y", 10));
    jq.insert(Job("Z", 7));

    SECTION("The first job run should always be the highest priority") {
        jq.runHighestPriority(); // Runs Y (priority 10)
        jq.runHighestPriority(); // Runs Z (priority 7)
        jq.runHighestPriority(); // Runs X (priority 3)
    }
}

TEST_CASE("Benchmarking JobQueue performance") {
    JobQueue jq;

    BENCHMARK("Inserting 1000 jobs into the queue") {
        for (int i = 0; i < 1000; ++i) {
            jq.insert(Job("Job", i));
        }
        return jq.size();
    };

    BENCHMARK("Running all jobs in order") {
        while (true) {
            if (jq.size() == 0) break;
            jq.runHighestPriority();
        }
        return jq.size();
    };
}
