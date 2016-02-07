#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <iostream>
#include "LRUCache.hxx"

struct SimpleTimer
{
    SimpleTimer() : startTimestamp_(std::chrono::system_clock::now()) {}
    ~SimpleTimer()
    {
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - startTimestamp_).count();
        std::cout << elapsedTime << " microseconds" << std::endl;
    }

private:
    std::chrono::system_clock::time_point startTimestamp_;
};

void InsertSpeedTest(const int elements, const int cacheSize)
{
    std::cout << "---------- " << __func__ << " ----------" << std::endl;
    using KeyType = int;
    using ValueType = int;

    LRUCache<KeyType, ValueType> container1(cacheSize);
    std::cout << "Using LRUCache(" << cacheSize << "), inserting " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            container1.insert({ i, i });
        }
    }

    std::unordered_map<KeyType, ValueType> container2;
    std::cout << "Using std::unordered_map, inserting " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            container2.insert({ i, i });
        }
    }

    std::map<KeyType, ValueType> container3;
    std::cout << "Using std::map, inserting " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            container3.insert({ i, i });
        }
    }

    std::list<ValueType> container4;
    std::cout << "Using std::list, pushing back " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            container4.push_back(i);
        }
    }

    std::vector<ValueType> container5;
    std::cout << "Using std::vector, pushing back " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            container5.push_back(i);
        }
    }
}

void FindSpeedTest(const int elements, const int cacheSize)
{
    std::cout << "---------- " << __func__ << " ----------" << std::endl;
    using KeyType = int;
    using ValueType = int;

    LRUCache<KeyType, ValueType> container1(cacheSize);
    for (int i = 0; i < elements; ++i) { container1.insert({ i, i }); }
    std::cout << "Using LRUCache(" << cacheSize << "), finding " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            volatile auto it = container1.find(i);
            //container1.find(i);
        }
    }

    std::unordered_map<KeyType, ValueType> container2;
    for (int i = 0; i < elements; ++i) { container2.insert({ i, i }); }
    std::cout << "Using std::unordered_map, finding " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            //volatile auto it = container2.find(i);
            container2.find(i);
        }
    }

    std::map<KeyType, ValueType> container3;
    for (int i = 0; i < elements; ++i) { container3.insert({ i, i }); }
    std::cout << "Using std::map, finding " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            //volatile auto it = container3.find(i);
            container3.find(i);
        }
    }

    std::list<ValueType> container4;
    for (int i = 0; i < elements; ++i) { container4.push_back(i); }
    std::cout << "Using std::list, finding " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            std::find(container4.begin(), container4.end(), i);
        }
    }

    std::vector<ValueType> container5;
    for (int i = 0; i < elements; ++i) { container5.push_back(i); }
    std::cout << "Using std::vector, finding " << elements << " elements: ";
    {
        SimpleTimer insertTimer;
        for (int i = 0; i < elements; ++i)
        {
            std::find(container5.begin(), container5.end(), i);
        }
    }
}

int main()
{
    // TODO: use argc/argv
    const auto lruSize = 10000;
    const auto elements = 10000;

    InsertSpeedTest(elements, lruSize);
    FindSpeedTest(elements, lruSize);
    return 0;
}