#include <gtest/gtest.h>
#include "../src/cache.h"

// Test 1 - Cold cache should have all compulsory misses
TEST(CacheTest, ColdCacheAllCompulsoryMisses) {
    Cache c(1024, 32, 2);
    EXPECT_FALSE(c.access(0x0));
    EXPECT_FALSE(c.access(0x20));
    EXPECT_FALSE(c.access(0x40));
    EXPECT_EQ(c.totalAccesses, 3);
    EXPECT_EQ(c.totalHits, 0);
    EXPECT_EQ(c.compulsoryMisses, 3);
    EXPECT_EQ(c.conflictMisses, 0);
}

// Test 2 - Second access to same address should be a hit
TEST(CacheTest, RepeatedAccessIsHit) {
    Cache c(1024, 32, 2);
    EXPECT_FALSE(c.access(0x0));  // miss
    EXPECT_TRUE(c.access(0x0));   // hit
    EXPECT_EQ(c.totalHits, 1);
}

// Test 3 - Conflict miss detection
TEST(CacheTest, ConflictMissDetected) {
    Cache c(1024, 32, 1); // 1-way so conflict happens
    EXPECT_FALSE(c.access(0x0));    // compulsory miss
    EXPECT_FALSE(c.access(0x400)); // compulsory miss - evicts 0x0
    EXPECT_FALSE(c.access(0x0));    // conflict miss
    EXPECT_EQ(c.conflictMisses, 1);
}

// Test 4 - 2-way cache eliminates conflict between 2 addresses
TEST(CacheTest, TwoWayEliminatesConflict) {
    Cache c(1024, 32, 2);
    c.access(0x0);
    c.access(0x400);
    EXPECT_TRUE(c.access(0x0));   // should be hit now
    EXPECT_TRUE(c.access(0x400)); // should be hit now
    EXPECT_EQ(c.conflictMisses, 0);
}

// Test 5 - Hit rate calculation
TEST(CacheTest, HitRateCalculation) {
    Cache c(1024, 32, 2);
    c.access(0x0);
    c.access(0x20);
    c.access(0x0);
    c.access(0x20);
    EXPECT_EQ(c.totalAccesses, 4);
    EXPECT_EQ(c.totalHits, 2);
    EXPECT_EQ(c.totalMisses, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}