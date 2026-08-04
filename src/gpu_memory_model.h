#pragma once
#include <vector>
#include <cstdint>
#include <string>

struct WarpAccess {
    std::vector<uint64_t> addresses;
    int numThreads;
    bool isCoalesced;
    int memoryTransactions;
};

class GPUMemoryModel {
public:
    int totalWarps = 0;
    int coalescedWarps = 0;
    int uncoalescedWarps = 0;
    int totalTransactions = 0;

    GPUMemoryModel(int numThreadsPerWarp = 32, int cacheLineSize = 128);
    WarpAccess accessCoalesced(uint64_t baseAddress);
    WarpAccess accessUncoalesced(uint64_t baseAddress, int stride);
    void printStats();

private:
    int threadsPerWarp;
    int cacheLineSize;
    int analyzeTransactions(const std::vector<uint64_t>& addresses);
};