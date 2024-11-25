#include "header.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random generator

int main() {
    // Simulation parameters
    const int MIN_LEASE = 40;
    const int MAX_LEASE = 70;
    const int MIN_SIZE = 50;
    const int MAX_SIZE = 350;
    const int TIME_LIMIT = 1000;
    const int REQUEST_INTERVAL = 10;
    const int MEMORY_SIZE = 1000;

    // Initialize clock and data structures
    long int clock = 0;
    freelist f = {{0, 500}};  // Initial free block: entire memory is free initially
    alloclist a;                      // Empty allocated list

    // Statistics tracking variables
    int totalRequests = 0;
    int satisfiedRequests = 0;
    int unsatisfiedRequests = 0;
    int totalBlockSize = 0;
    int minBlockSize = MAX_SIZE;
    int maxBlockSize = MIN_SIZE;
    int totalLeaseDuration = 0;
    int minLeaseDuration = MAX_LEASE;
    int maxLeaseDuration = MIN_LEASE;
    int mergeCount = 0;

    srand(time(0));  // Seed the random number generator

    // Main simulation loop
    while (++clock <= TIME_LIMIT) {
        // Check for expired leases at each tick
        checkExpiredLeases(a, f, clock);

        // Generate a request at regular intervals
        if (clock % REQUEST_INTERVAL == 0) {
            int leaseDuration;
            range request = generateRequest(MIN_SIZE, MAX_SIZE, leaseDuration, MIN_LEASE, MAX_LEASE);
            totalRequests++;
            totalBlockSize += request.second;

            // Update block size statistics
            if (request.second < minBlockSize) minBlockSize = request.second;
            if (request.second > maxBlockSize) maxBlockSize = request.second;

            // Update lease duration statistics
            totalLeaseDuration += leaseDuration;
            if (leaseDuration < minLeaseDuration) minLeaseDuration = leaseDuration;
            if (leaseDuration > maxLeaseDuration) maxLeaseDuration = leaseDuration;

            // Try to allocate the requested block
            if (allocateBlock(f, a, request.second, clock, leaseDuration)) {
                satisfiedRequests++;
            } else {
                // Attempt merging adjacent free blocks and retry
                mergeFreeBlocks(f);
                mergeCount++;

                if (allocateBlock(f, a, request.second, clock, leaseDuration)) {
                    satisfiedRequests++;
                } else {
                    unsatisfiedRequests++;
                   // std::cout << "Allocation failed for request size: " << request.second << "\n";
                }
            }
        }
    }

    // Generate the final simulation report
    generateReport(totalRequests, satisfiedRequests, unsatisfiedRequests, 
                   minBlockSize, maxBlockSize, totalBlockSize, 
                   minLeaseDuration, maxLeaseDuration, totalLeaseDuration, 
                   mergeCount, f, a);

    return 0;
}
