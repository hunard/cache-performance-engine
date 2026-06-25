#include <iostream>
#include "cache.h"

int main() {
    // TEST 1 - Cold cache (all compulsory misses)
    std::cout << "=== TEST 1: Cold Cache ===" << std::endl;
    Cache c1(1024, 32);
    uint64_t coldAddresses[] = {0x0, 0x20, 0x40, 0x60, 0x80};
    for (auto addr : coldAddresses) {
        bool hit = c1.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c1.printStats();

    // TEST 2 - Perfect locality (hits after warmup)
    std::cout << "\n=== TEST 2: Perfect Locality ===" << std::endl;
    Cache c2(1024, 32);
    uint64_t localAddresses[] = {0x0, 0x20, 0x40, 0x0, 0x20, 0x40};
    for (auto addr : localAddresses) {
        bool hit = c2.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c2.printStats();

    // TEST 3 - Forced conflict misses
    std::cout << "\n=== TEST 3: Conflict Pattern ===" << std::endl;
    Cache c3(1024, 32);
    uint64_t conflictAddresses[] = {0x0, 0x400, 0x0, 0x400, 0x0};
    for (auto addr : conflictAddresses) {
        bool hit = c3.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c3.printStats();
}
