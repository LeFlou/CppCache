#pragma once

#include <list>
#include <cassert>
#include <unordered_map>

template <typename _Kty, typename _Ty, size_t _Size>
class LRUCache
{
public:
    using value_type = std::pair<const _Kty, _Ty>;

private:
    const size_t maxSize_ = _Size;
    std::list<value_type> values_;

public:
    using value_iterator = decltype(values_.begin());
    using mapping_type = std::unordered_map<_Kty, value_iterator>;
    using mapping_iterator = typename mapping_type::iterator;

private:
    mapping_type mapping_;

public:
    LRUCache() = default;
    ~LRUCache() = default;
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = default;
    LRUCache& operator=(LRUCache&&) = default;

    std::pair<mapping_iterator, bool> insert(const value_type& value)
    {
        static_assert(_Size > 0, "Size must be greater than zero.");

        values_.push_back(value);
        auto result = mapping_.insert({ value.first, --values_.end() });

        if (values_.size() > _Size)
        {
            const auto& oldestValue = values_.front();
            mapping_.erase(oldestValue.first);
            values_.pop_front();
        }

        return std::make_pair(result.first, true);
    }

    _Ty& operator[](const _Kty& key)
    {
        auto it = mapping_.find(key);
        if (it != mapping_.cend())
        {
            return it->second->second;
        }
        auto result = insert({ key , _Ty{} });
        return result.first->second->second;
    }

    size_t size() const
    {
        assert(values_.size() == mapping_.size());
        return values_.size();
    }

    bool empty() const
    {
        return values_.empty();
    }
};
