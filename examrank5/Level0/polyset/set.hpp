#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
private:
    searchable_bag *bag;
    set() : bag(0) {}

public:
    set(searchable_bag &b) : bag(&b) {}
    set(const set &other) : bag(other.bag) {}
    ~set() {}

    set &operator=(const set &other)
    {
        if (this != &other)
            bag = other.bag;
        return *this;
    }

    void insert(int item)
    {
        if (bag && !bag->has(item))
            bag->insert(item);
    }

    void insert(int *items, int n)
    {
        for (int i = 0; i < n; i++)
            insert(items[i]);
    }

    void print() const { bag->print(); }
    void clear() { bag->clear(); }
    bool has(int item) const { return bag->has(item); }
    searchable_bag &get_bag() const { return *bag; }
};

#endif