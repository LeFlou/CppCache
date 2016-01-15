#pragma once

#include <list>
#include <cassert>
#include <unordered_map>

template <typename _Kty, typename _Ty, size_t _Size>
class LRUCache
{
    const size_t maxSize_ = _Size;
    std::list<_Ty> values_;

public:
    using value_iterator = decltype(*values_.begin());
    using value_type = std::pair<const _Kty, _Ty>;
    using mapping_type = std::unordered_map<_Kty, value_iterator>;
    using iterator_type = typename mapping_type::iterator;

private:
    mapping_type mapping_;
    iterator_type oldest_ {};

public:
    LRUCache() = default;
    ~LRUCache() = default;
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = default;
    LRUCache& operator=(LRUCache&&) = default;

    bool insert(const value_type& value)
    {
        static_assert(_Size > 0, "Size must be greater than zero.");
        if (values_.size() == _Size)
        {
            auto itToRemove = values_.cbegin();
            values_.erase(itToRemove);

            assert(oldest_ != mapping_.end());
            mapping_.erase(oldest_);
            oldest_ = mapping_.begin();
        }

        values_.push_back(value.second);
        mapping_.insert({ value.first, values_.back() });

        assert(values_.size() == mapping_.size());
        if (values_.size() == 1)
        {
            oldest_ = mapping_.begin();
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
        static _Ty dummy{};
        return dummy;
    }

    size_t size() const
    {
        return values_.size();
    }
};
