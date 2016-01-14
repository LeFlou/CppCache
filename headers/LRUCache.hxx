#pragma once

#include <vector>
#include <cassert>
#include <unordered_map>

template <typename _Kty, typename _Ty, size_t Size>
class LRUCache
{
    const size_t maxSize_ = Size;
    std::vector<_Ty> values_;

public:
    using value_iterator = decltype(*values_.begin());
    using value_type = std::pair<const _Kty, _Ty>;

private:
    std::unordered_map<_Kty, value_iterator> mapping_;

public:
    LRUCache() = default;
    ~LRUCache() = default;
    LRUCache(const LRUCache&) = default;
    LRUCache& operator=(const LRUCache&) = default;
    LRUCache(LRUCache&&) = default;
    LRUCache& operator=(LRUCache&&) = default;

    bool insert(const value_type& value)
    {
        if (values_.size() == Size)
        {
            // Remove one element
            auto itToRemove = values_.cbegin();
            // TODO: erase oldest iterator from mapping_
            values_.erase(itToRemove);
        }

        values_.push_back(value.second);
        mapping_.insert({ value.first, values_.back() });

        assert(values_.size() == mapping_.size());
        if (values_.size() == 1)
        {
            // TODO: assign mapping_.cbegin() to oldest
        }

        return true;
    }

    _Ty& operator[](const _Kty& key)
    {
        auto it = mapping_.find(key);
        if (it != mapping_.cend())
        {
            return it->second;
        }

        // TODO: remove dummy and brace initialize
        static _Ty dummy {};
        return dummy;
    }

    size_t size() const
    {
        return values_.size();
    }
};