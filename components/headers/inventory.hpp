#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "globals.hpp"
#include "item.hpp"
#include <iostream>
using namespace std;


class Inventory{
    private:
        Item** inv_buffer;
    public:
        Inventory();
        ~Inventory();
        Item get(int i, int j);
        void set(int i, int j, Item* item);
        void display();
        void add(Item* item, int quant);
};

#endif