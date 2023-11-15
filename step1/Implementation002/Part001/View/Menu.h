#pragma once
#ifndef HEADER_MENU
#define HEADER_MENU

#include <string>
#include <vector>
#include <algorithm>
#include "Item.h"
// TODO : Make the menu resposible for the destruction of the pointers
//        Think about it, not sure who is responsible for it
//        Maybe is time to use some shared_ptrs
class Menu
{
private:
    Menu *_previous;
    std::string _description;
    std::vector<Item *> _items;
    std::vector<Menu *> _menus;
    std::string _key;

public:
    Menu(auto pv, auto dt, auto k) : _previous(pv), _description(dt), _key(k) {}

    auto description() const noexcept -> std::string
    {
        return _description;
    }

    auto previous() const -> Menu *
    {
        return _previous;
    }

    auto items() const noexcept -> std::vector<Item *>
    {
        return _items;
    }

    auto menus() const noexcept -> std::vector<Menu *>
    {
        return _menus;
    }

    auto add(Item *it) -> Menu &
    {
        _items.push_back(it);

        return *this;
    }

    auto add(Menu *mn) -> Menu &
    {
        _menus.push_back(mn);

        return *this;
    }

    bool isKey(const std::string & k)
    {
        return _key.compare(k) == 0;
    }

    auto key() const noexcept -> std::string
    {
        return _key;
    }

    // If it find an item, it will trigger and not change menus (return this)
    // If it doen't find and item, it will search for intern menus
    // If it find an intern menu, it returns the internal menu
    // If it doesn't find an intern menu, it won't change (return this)
    Menu * triggerKey(const std::string & k)
    {
        if (auto it = std::find_if(std::begin(_items), std::end(_items), 
            [&k](Item *item) {
                if (item->isKey(k)) 
                {
                    item->trigger();
                    return true;
                }
                return false; 
            }); 
        it == std::end(_items)
        )
        {
            auto it2 = std::find_if(std::begin(_menus), std::end(_menus), 
            [&k](Menu * menu) {
                if (menu->isKey(k)) 
                {
                    return true;
                }
                return false; 
            });
            if (it2 != std::end(_menus))
            {
                return *it2;
            }
        }
        return this;
    }
};
#endif // HEADER_MENU