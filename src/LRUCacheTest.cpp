#include <gtest/gtest.h>
#include "LRUCache.hxx"

TEST(LRUCache, Size)
{
    LRUCache<int, std::string, 1> cache;
    EXPECT_EQ(0, cache.size());

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_EQ(1, cache.size());

    cache.insert(std::make_pair<int, std::string>(1, "2"));
    EXPECT_EQ(1, cache.size());
}

TEST(LRUCache, Empty)
{
    LRUCache<int, std::string, 1> cache;
    EXPECT_TRUE(cache.empty());

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_FALSE(cache.empty());

    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_FALSE(cache.empty());
}

TEST(LRUCache, InsertPair)
{
    LRUCache<int, std::string, 3> cache;

    auto pairResult = cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_EQ(std::string("1"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(1, cache.size());

    pairResult = cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(std::string("2"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(2, cache.size());

    pairResult = cache.insert(std::make_pair<int, std::string>(3, "3"));
    EXPECT_EQ(std::string("3"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());

    pairResult = cache.insert(std::make_pair<int, std::string>(4, "4"));
    EXPECT_EQ(std::string("4"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());
}

TEST(LRUCache, BracketOperator)
{
    LRUCache<int, std::string, 5> cache;

    // Element does exist
    cache.insert(std::make_pair<int, std::string>(1, "1"));
    auto& value = cache[1];
    EXPECT_EQ(std::string("1"), value);

    // Element that does not exist
    auto& defaultValue = cache[42];
    EXPECT_EQ(std::string(), defaultValue);
}