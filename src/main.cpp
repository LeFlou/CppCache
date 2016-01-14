#include <string>
#include <iostream>
#include "LRUCache.hxx"

int main()
{
    LRUCache<int, std::string, 5> myLRU;

    myLRU.insert(std::make_pair<int, std::string>(42, "lol"));
    auto myString = myLRU[42];

    std::cout << myString << std::endl;

    return 0;
}