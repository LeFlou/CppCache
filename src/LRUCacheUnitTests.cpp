#include <gtest/gtest.h>
#include "LRUCache.hxx"

TEST(LRUCache, InsertPair)
{
    LRUCache<int, std::string> cache(3);

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

TEST(LRUCache, Erase)
{
    LRUCache<std::string, double> cache(2);

    const auto firstKey = std::string("KeyOne");
    const auto secondKey = std::string("KeyTwo");
    const auto thirdKey = std::string("KeyThree");
    const auto firstValue = 1.0;
    const auto secondValue = 2.0;

    EXPECT_FALSE(cache.erase(firstKey));

    // Inserting first key/value
    // Erasing (not yet inserted) second key
    cache.insert({ firstKey, firstValue });
    EXPECT_FALSE(cache.erase(secondKey));

    // Inserting second key/value
    // Erasing (present) first key
    cache.insert({ secondKey, secondValue });
    EXPECT_TRUE(cache.erase(firstKey));
    EXPECT_EQ(1, cache.size());

    // Erasing (not present) first key
    EXPECT_FALSE(cache.erase(firstKey));
    EXPECT_EQ(1, cache.size());

    // Erasing (present) second key
    EXPECT_TRUE(cache.erase(secondKey));
    EXPECT_TRUE(cache.empty());

    cache[thirdKey];
    EXPECT_EQ(1, cache.size());
    EXPECT_TRUE(cache.erase(thirdKey));
    EXPECT_TRUE(cache.empty());
}

TEST(LRUCache, Find)
{
    LRUCache<int, std::string> cache(2);

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
    LRUCache<int, std::string> cache(2);

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
    LRUCache<int, std::string> cache(2);
    EXPECT_EQ(0, cache.size());

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_EQ(1, cache.size());

    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(2, cache.size());
}

TEST(LRUCache, Empty)
{
    LRUCache<int, std::string> cache(1);
    EXPECT_TRUE(cache.empty());

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    EXPECT_FALSE(cache.empty());

    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_FALSE(cache.empty());
}

TEST(LRUCache, Clear)
{
    LRUCache<int, std::string> cache(2);

    cache.insert(std::make_pair<int, std::string>(1, "1"));
    cache.insert(std::make_pair<int, std::string>(2, "2"));
    EXPECT_EQ(2, cache.size());

    cache.clear();
    EXPECT_TRUE(cache.empty());
}

TEST(LRUCache, BracketOperatorLValue)
{
    LRUCache<std::string, std::string> cache(5);

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
    LRUCache<std::string, std::string> cache(5);

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