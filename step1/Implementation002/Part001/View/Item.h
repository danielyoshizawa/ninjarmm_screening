#pragma once
#ifndef HEADER_ITEM
#define HEADER_ITEM

#include <string>
#include <functional>

class Item
{
private:
    std::function<void(void)> _callback;
    std::string _description;
    std::string _key;
public:
    Item(auto cb, auto dt, auto k) : _callback{cb}, _description{dt}, _key{k} {}

    void trigger()
    {
        _callback();
    }

    std::string description() const noexcept
    {
        return _description;
    }

    auto isKey(const std::string & k) const noexcept -> bool
    {
        return _key.compare(k) == 0;
    }

    auto key() const noexcept -> std::string
    {
        return _key;
    }
};
#endif // HEADER_ITEM