#include "cache.h"
#include <iostream>
#include <cmath>
#include <climits>

Cache::Cache(int cacheSizeBytes, int blockSizeBytes, int numWays) {
    this->numWays = numWays;
    numSets = (cacheSizeBytes / blockSizeBytes) / numWays;
    blockBits = std::log2(blockSizeBytes);
    indexBits = std::log2(numSets);
    sets.resize(numSets, std::vector<CacheLine>(numWays));
}

bool Cache::access(uint64_t address) {
    uint64_t index = (address >> blockBits) & ((1 << indexBits) - 1);
    uint64_t tag   = address >> (blockBits + indexBits);

    totalAccesses++;

    // search all ways in this set for a hit
    for (int i = 0; i < numWays; i++) {
        if (sets[index][i].valid && sets[index][i].tag == tag) {
            totalHits++;
            // update LRU counter
            sets[index][i].lruCounter = totalAccesses;
            return true;
        }
    }

    // miss
    totalMisses++;
    uint64_t blockNumber = address >> blockBits;
    if (seenBlocks.find(blockNumber) == seenBlocks.end()) {
        compulsoryMisses++;
    } else {
        conflictMisses++;
    }
    seenBlocks.insert(blockNumber);

    // find empty way first
    for (int i = 0; i < numWays; i++) {
        if (!sets[index][i].valid) {
            sets[index][i] = {true, tag, totalAccesses};
            return false;
        }
    }

    // all ways full - evict LRU
    int lruWay = 0;
    for (int i = 1; i < numWays; i++) {
        if (sets[index][i].lruCounter < sets[index][lruWay].lruCounter) {
            lruWay = i;
        }
    }
    sets[index][lruWay] = {true, tag, totalAccesses};
    return false;
}

void Cache::printStats() {
    std::cout << "\n--- Cache Stats ---" << std::endl;
    std::cout << "Total Accesses:    " << totalAccesses << std::endl;
    std::cout << "Hits:              " << totalHits << std::endl;
    std::cout << "Misses:            " << totalMisses << std::endl;
    std::cout << "Hit Rate:          " << (100.0 * totalHits / totalAccesses) << "%" << std::endl;
    std::cout << "Compulsory Misses: " << compulsoryMisses << std::endl;
    std::cout << "Conflict Misses:   " << conflictMisses << std::endl;
}