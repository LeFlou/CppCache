#include <string>
#include <iostream>
#include "LRUCache.hxx"

int main()
{
    LRUCache<int, std::string, 3> myLRU;

    myLRU.insert(std::make_pair<int, std::string>(1, "1"));
    myLRU.insert(std::make_pair<int, std::string>(2, "2"));
    myLRU.insert(std::make_pair<int, std::string>(3, "3"));
    myLRU.insert(std::make_pair<int, std::string>(4, "4"));

    auto myString = myLRU[42];

    std::cout << myString << std::endl;

    return 0;
}