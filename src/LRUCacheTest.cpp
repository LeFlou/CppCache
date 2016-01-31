#include <gtest/gtest.h>
#include "LRUCache.hxx"

TEST(LRUCache, InsertPair)
{
    LRUCache<int, std::string, 3> cache;

    auto pairResult = cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_EQ(std::string("1"), pairResult.first->second->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(1, cache.size());

    pairResult = cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(std::string("2"), pairResult.first->second->second);
    EXPECT_TRUE(pairResult.second);

    pairResult = cache.insert(std::make_pair<int, std::string>(3, "3"));
    EXPECT_EQ(std::string("3"), pairResult.first->second->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());

    // Reaching limit
    pairResult = cache.insert(std::make_pair<int, std::string>(4, "4"));
    EXPECT_EQ(std::string("4"), pairResult.first->second->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());

    // Trying to insert another value with previous key
    pairResult = cache.insert(std::make_pair<int, std::string>(4, "42"));
    EXPECT_EQ(std::string("4"), pairResult.first->second->second);
    EXPECT_FALSE(pairResult.second);
    EXPECT_EQ(3, cache.size());
}

TEST(LRUCache, Count)
{
    LRUCache<int, std::string, 2> cache;

    const auto firstKey = 1;
    const auto secondKey = 2;
    const auto thirdKey = 3;
    const auto firstValue = std::string("1");
    const auto secondValue = std::string("2");

    cache.insert(std::make_pair(firstKey, firstValue));
    cache.insert(std::make_pair(secondKey, secondValue));

    EXPECT_EQ(1, cache.count(firstKey));
    EXPECT_EQ(1, cache.count(secondKey));
    EXPECT_EQ(0, cache.count(thirdKey));
}

TEST(LRUCache, Size)
{
    LRUCache<int, std::string, 2> cache;
    EXPECT_EQ(0, cache.size());

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_EQ(1, cache.size());

    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(2, cache.size());
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

TEST(LRUCache, Clear)
{
    LRUCache<int, std::string, 2> cache;

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(2, cache.size());

    cache.clear();
    EXPECT_TRUE(cache.empty());
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