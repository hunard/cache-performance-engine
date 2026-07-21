#include <iostream>
#include "cache.h"
#include "trace_reader.h"
int main() {
    // TEST 1 - Cold cache (all compulsory misses)
    std::cout << "=== TEST 1: Cold Cache ===" << std::endl;
    Cache c1(1024, 32, 2); // 2-way set associative
    uint64_t coldAddresses[] = {0x0, 0x20, 0x40, 0x60, 0x80};
    for (auto addr : coldAddresses) {
        bool hit = c1.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c1.printStats();

    // TEST 2 - Perfect locality (hits after warmup)
    std::cout << "\n=== TEST 2: Perfect Locality ===" << std::endl;
    Cache c2(1024, 32,2);
    uint64_t localAddresses[] = {0x0, 0x20, 0x40, 0x0, 0x20, 0x40};
    for (auto addr : localAddresses) {
        bool hit = c2.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c2.printStats();

    // TEST 3 - Forced conflict misses
    std::cout << "\n=== TEST 3: Conflict Pattern ===" << std::endl;
    Cache c3(1024, 32,2);
    uint64_t conflictAddresses[] = {0x0, 0x400, 0x0, 0x400, 0x0};
    for (auto addr : conflictAddresses) {
        bool hit = c3.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }
    c3.printStats();
    // TEST 4 - Compare 1-way vs 2-way vs 4-way on conflict pattern
std::cout << "\n=== TEST 4: Associativity Comparison ===" << std::endl;

uint64_t compareAddresses[] = {0x0, 0x400, 0x800, 0x0, 0x400, 0x800};

std::cout << "\n1-way (direct-mapped):" << std::endl;
Cache c4(1024, 32, 1);
for (auto addr : compareAddresses) {
    bool hit = c4.access(addr);
    std::cout << "0x" << std::hex << addr << " -> " << (hit ? "HIT" : "MISS") << std::endl;
}
c4.printStats();

std::cout << "\n2-way:" << std::endl;
Cache c5(1024, 32, 2);
for (auto addr : compareAddresses) {
    bool hit = c5.access(addr);
    std::cout << "0x" << std::hex << addr << " -> " << (hit ? "HIT" : "MISS") << std::endl;
}
c5.printStats();

std::cout << "\n4-way:" << std::endl;
Cache c6(1024, 32, 4);
for (auto addr : compareAddresses) {
    bool hit = c6.access(addr);
    std::cout << "0x" << std::hex << addr << " -> " << (hit ? "HIT" : "MISS") << std::endl;
}
c6.printStats();
// TEST 5 - LRU vs FIFO comparison
std::cout << "\n=== TEST 5: LRU vs FIFO ===" << std::endl;

uint64_t policyAddresses[] = {0x0, 0x400, 0x0, 0x800, 0x0};

std::cout << "\nLRU (2-way):" << std::endl;
Cache c7(1024, 32, 2, true);
for (auto addr : policyAddresses) {
    bool hit = c7.access(addr);
    std::cout << "0x" << std::hex << addr << " -> " << (hit ? "HIT" : "MISS") << std::endl;
}
c7.printStats();

std::cout << "\nFIFO (2-way):" << std::endl;
Cache c8(1024, 32, 2, false);
for (auto addr : policyAddresses) {
    bool hit = c8.access(addr);
    std::cout << "0x" << std::hex << addr << " -> " << (hit ? "HIT" : "MISS") << std::endl;
}
c8.printStats();
// TEST 6 - Real trace analysis
std::cout << std::dec;
std::cout << "\n=== TEST 6: Real Trace Analysis ===" << std::endl;

std::cout << "\nMatrix Multiply (2-way, 1KB cache):" << std::endl;
Cache matrixCache(1024, 32, 2);
TraceReader matrixReader("traces/matrix.trace");
if (matrixReader.isOpen()) {
    uint64_t addr;
    while (matrixReader.nextAddress(addr)) {
        matrixCache.access(addr);
    }
    matrixCache.printStats();
}

std::cout << "\nLinked List (2-way, 1KB cache):" << std::endl;
Cache linkedCache(1024, 32, 2);
TraceReader linkedReader("traces/linkedlist.trace");
if (linkedReader.isOpen()) {
    uint64_t addr;
    while (linkedReader.nextAddress(addr)) {
        linkedCache.access(addr);
    }
    linkedCache.printStats();
}
}
