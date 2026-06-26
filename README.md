# Cache Performance Analysis Engine

A low-level cache simulator built in C++ that models how memory access patterns
interact with CPU cache behavior — built to answer one question: why does the 
same data access run at wildly different speeds depending on how it touches memory.

---

## What it does

- Simulates a direct-mapped cache with configurable size and block size
- Decomposes memory addresses into tag, index, and offset
- Detects cache hits and misses on every memory access
- Classifies every miss as either **compulsory** or **conflict**
- Reports hit rate, total accesses, hits, and misses

---

## Why cache performance matters

Cache is the small, fast memory sitting between your CPU and RAM. Every time
the CPU needs data, it checks the cache first. A hit means instant access.
A miss means a trip to RAM — which can be 100x slower. The hit rate is the 
single number that determines how fast your program actually runs.

---

## Miss Classification

| Miss Type | Cause | Avoidable? |
|-----------|-------|------------|
| Compulsory | First time this memory block has ever been accessed | No |
| Conflict | Block was cached before but got evicted by another address mapping to the same slot | Yes |

---

## Build and Run

```bash
g++ -std=c++17 main.cpp cache.cpp -o cache && ./cache
```

---

## Sample Output
=== TEST 1: Cold Cache ===

Address 0x0 -> MISS

Address 0x20 -> MISS

Address 0x40 -> MISS

Address 0x60 -> MISS

Address 0x80 -> MISS

--- Cache Stats ---

Total Accesses:    5

Hits:              0

Misses:            5

Hit Rate:          0%

Compulsory Misses: 5

Conflict Misses:   0
=== TEST 2: Perfect Locality ===
Address 0x0 -> MISS

Address 0x20 -> MISS

Address 0x40 -> MISS

Address 0x0 -> HIT

Address 0x20 -> HIT

Address 0x40 -> HIT

--- Cache Stats ---

Total Accesses:    6

Hits:              3

Misses:            3

Hit Rate:          50%

Compulsory Misses: 3

Conflict Misses:   0
=== TEST 3: Conflict Pattern ===

Address 0x0 -> MISS

Address 0x400 -> MISS

Address 0x0 -> MISS

Address 0x400 -> MISS

Address 0x0 -> MISS
--- Cache Stats ---

Total Accesses:    5

Hits:              0

Misses:            5

Hit Rate:          0%

Compulsory Misses: 2

Conflict Misses:   3

---

## Project Structure
cache-performance-engine/

├── cache.h          → Cache class declaration

├── cache.cpp        → Cache implementation

├── main.cpp         → Test suite

└── docs/

└── design_decisions.md

---

## Roadmap

- [x] Phase 1 — Direct-mapped cache simulator with miss classification
- [ ] Phase 2 — Set-associative cache with LRU and FIFO replacement policies
- [ ] Phase 3 — Real memory trace analysis with Python visualization
- [ ] Phase 4 — GPU memory coalescing model
- [ ] Phase 5 — Benchmarking report and final documentation