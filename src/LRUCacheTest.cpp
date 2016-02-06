#include <gtest/gtest.h>
#include "LRUCache.hxx"

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

    pairResult = cache.insert(std::make_pair<int, std::string>(3, "3"));
    EXPECT_EQ(std::string("3"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());

    // Reaching limit
    pairResult = cache.insert(std::make_pair<int, std::string>(4, "4"));
    EXPECT_EQ(std::string("4"), pairResult.first->second);
    EXPECT_TRUE(pairResult.second);
    EXPECT_EQ(3, cache.size());

    // Trying to insert another value with previous key
    pairResult = cache.insert(std::make_pair<int, std::string>(4, "42"));
    EXPECT_EQ(std::string("4"), pairResult.first->second);
    EXPECT_FALSE(pairResult.second);
    EXPECT_EQ(3, cache.size());
}

TEST(LRUCache, Find)
{
    LRUCache<int, std::string, 2> cache;

    const auto firstKey = 1;
    const auto secondKey = 2;
    const auto thirdKey = 3;
    const auto firstValue = std::string("1");
    const auto secondValue = std::string("2");

    cache.insert(std::make_pair(firstKey, firstValue));
    cache.insert(std::make_pair(secondKey, secondValue));

    auto firstResult = cache.find(firstKey);
    auto secondResult = cache.find(secondKey);
    auto thirdResult = cache.find(thirdKey);

    EXPECT_TRUE(firstResult.second);
    EXPECT_EQ(firstKey, firstResult.first->first);
    EXPECT_EQ(firstValue, firstResult.first->second);

    EXPECT_TRUE(secondResult.second);
    EXPECT_EQ(secondKey, secondResult.first->first);
    EXPECT_EQ(secondValue, secondResult.first->second);

    EXPECT_FALSE(thirdResult.second);
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

TEST(LRUCache, BracketOperatorLValue)
{
    LRUCache<std::string, std::string, 5> cache;

    const auto firstKey = std::string("answer to life the universe and everything");
    const auto firstValue = std::string("42");
    const auto secondKey = std::string("where's north ?");

    cache.insert(std::make_pair(firstKey, firstValue));

    // Element does exist
    auto& value = cache[firstKey];
    EXPECT_EQ(firstValue, value);

    // Element that does not exist
    auto& defaultValue = cache[secondKey];
    EXPECT_EQ(std::string(), defaultValue);
}

TEST(LRUCache, BracketOperatorRValue)
{
    LRUCache<std::string, std::string, 5> cache;

    const char* const firstKey = "answer to life the universe and everything";
    const char* const firstValue = "42";
    const char* const secondKey = "where's north ?";

    // Element does exist
    cache.insert(std::make_pair(std::string(firstKey), std::string(firstValue)));
    auto& value = cache[std::string(firstKey)];
    EXPECT_EQ(std::string(firstValue), value);

    // Element that does not exist
    auto& defaultValue = cache[std::string(secondKey)];
    EXPECT_EQ(std::string(), defaultValue);
}