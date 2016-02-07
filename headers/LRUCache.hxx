#pragma once

#include <list>
#include <cassert>
#include <unordered_map>

template <typename _Kty, typename _Ty>
class LRUCache
{
public:
    using value_type = std::pair<const _Kty, _Ty>;

private:
    int fixedCacheSize_;
    std::list<value_type> values_;

public:
    using value_iterator = decltype(values_.begin());
    using mapping_type = std::unordered_map<_Kty, value_iterator>;
    using mapping_iterator = typename mapping_type::iterator;

private:
    mapping_type mapping_;

public:
    LRUCache(const int cacheSize)
        : fixedCacheSize_(cacheSize)
    {
        if (fixedCacheSize_ <= 0)
        {
            throw std::logic_error("LRUCache size must be greater than zero");
        }
    }
    ~LRUCache() = default;
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = default;
    LRUCache& operator=(LRUCache&&) = default;

    // ---------
    // Modifiers
    // ---------
    std::pair<value_iterator, bool> insert(const value_type& value)
    {
        // Trying to insert dummy value
        auto result = mapping_.insert({ value.first, values_.end() });
        if (result.second == false)
        {
            return std::make_pair(result.first->second, false);
        }

        // Replace by input value
        values_.push_back(value);
        result.first->second = --values_.end();

        // Erase oldest value
        if (values_.size() > fixedCacheSize_)
        {
            const auto& oldestValue = values_.front();
            mapping_.erase(oldestValue.first);
            values_.pop_front();
        }

        return std::make_pair(result.first->second, true);
    }

    bool erase(const _Kty& key)
    {
        const auto mappingIt = mapping_.find(key);
        if (mappingIt != mapping_.end())
        {
            values_.erase(mappingIt->second);
            mapping_.erase(mappingIt);
            return true;
        }
        return false;
    }

    void clear()
    {
        values_.clear();
        mapping_.clear();
    }

    // --------------
    // Element access
    // --------------
    _Ty& operator[](const _Kty& key)
    {
        auto it = mapping_.find(key);
        if (it != mapping_.cend())
        {
            return it->second->second;
        }
        auto result = insert({ key , _Ty{} });
        return result.first->second;
    }

    _Ty& operator[](_Kty&& key)
    {
        auto it = mapping_.find(key);
        if (it != mapping_.cend())
        {
            return it->second->second;
        }
        auto result = insert({ std::move(key), _Ty{} });
        return result.first->second;
    }

    // --------
    // Capacity
    // --------
    bool empty() const noexcept
    {
        return values_.empty();
    }

    size_t size() const noexcept
    {
        assert(values_.size() == mapping_.size());
        return values_.size();
    }

    // --------------
    // Element lookup
    // --------------
    std::pair<value_iterator, bool> find(const _Kty& key)
    {
        auto mappingIt = mapping_.find(key);
        if (mappingIt != mapping_.end())
        {
            return std::make_pair(mappingIt->second, true);
        }
        return std::make_pair(values_.end(), false);
    }

    size_t count(const _Kty& key) const
    {
        return mapping_.count(key);
    }
};
