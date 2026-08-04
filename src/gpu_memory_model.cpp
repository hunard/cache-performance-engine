#include "gpu_memory_model.h"
#include <iostream>
#include <algorithm>
#include <set>

GPUMemoryModel::GPUMemoryModel(int numThreadsPerWarp, int cacheLineSize) {
    this->threadsPerWarp = numThreadsPerWarp;
    this->cacheLineSize = cacheLineSize;
}

int GPUMemoryModel::analyzeTransactions(const std::vector<uint64_t>& addresses) {
    // count unique cache lines touched
    std::set<uint64_t> cacheLines;
    for (auto addr : addresses) {
        cacheLines.insert(addr / cacheLineSize);
    }
    return cacheLines.size();
}

WarpAccess GPUMemoryModel::accessCoalesced(uint64_t baseAddress) {
    WarpAccess warp;
    warp.numThreads = threadsPerWarp;
    for (int i = 0; i < threadsPerWarp; i++) {
        warp.addresses.push_back(baseAddress + i * 4); // each thread reads 4 bytes
    }
    warp.memoryTransactions = analyzeTransactions(warp.addresses);
    warp.isCoalesced = (warp.memoryTransactions == 1);
    totalWarps++;
    totalTransactions += warp.memoryTransactions;
    if (warp.isCoalesced) coalescedWarps++;
    else uncoalescedWarps++;
    return warp;
}

WarpAccess GPUMemoryModel::accessUncoalesced(uint64_t baseAddress, int stride) {
    WarpAccess warp;
    warp.numThreads = threadsPerWarp;
    for (int i = 0; i < threadsPerWarp; i++) {
        warp.addresses.push_back(baseAddress + i * stride);
    }
    warp.memoryTransactions = analyzeTransactions(warp.addresses);
    warp.isCoalesced = (warp.memoryTransactions == 1);
    totalWarps++;
    totalTransactions += warp.memoryTransactions;
    if (warp.isCoalesced) coalescedWarps++;
    else uncoalescedWarps++;
    return warp;
}

void GPUMemoryModel::printStats() {
    std::cout << "\n--- GPU Memory Stats ---" << std::endl;
    std::cout << "Total Warps:          " << totalWarps << std::endl;
    std::cout << "Coalesced Warps:      " << coalescedWarps << std::endl;
    std::cout << "Uncoalesced Warps:    " << uncoalescedWarps << std::endl;
    std::cout << "Total Transactions:   " << totalTransactions << std::endl;
    std::cout << "Avg Transactions/Warp: " << (float)totalTransactions / totalWarps << std::endl;
}