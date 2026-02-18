#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

//1. class
class searchable_array_bag : public array_bag, public searchable_bag
{
public:
    searchable_array_bag() : array_bag() {}
    searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}
    ~searchable_array_bag() {}

    searchable_array_bag &operator=(const searchable_array_bag &other)
    {
        if (this != &other)
            array_bag::operator=(other);
        return *this;
    }

//2. bool function(has)
    bool has(int item) const
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == item)
                return true;
        }
        return false;
    }
};

#endif
