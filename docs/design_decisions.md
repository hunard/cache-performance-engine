# Design Decisions

## Why direct-mapped first?
Direct-mapped has exactly one slot per index, no replacement decision needed. This isolates the core address decomposition logic without adding policy complexity. Once the offset logic is proven correct, adding associativity becomes a controlled extension rather than a debugging nightmare.

## Why classify misses as compulsory vs conflict?
Total miss rate alone tells you nothing actionable. A 40% miss rate could mean your access pattern is cold (unavoidable) or your cache is too small and addresses
keep evicting each other (fixable). Separating the two gives you a diagnosis, not just a symptom.

## Why separate cache.h, cache.cpp, and main.cpp?
The header declares what the cache does. The implementation defines how it does it. Main only uses it. This means the cache logic can be tested, swapped, or extended without touching the entry point the same pattern used in production C++ codebases.