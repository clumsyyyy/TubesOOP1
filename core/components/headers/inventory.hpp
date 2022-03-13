#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "vars.hpp"
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
        void specify(int i, int j);
        void displayMenu();
        void displayDetails();
        void addNonTool(NonTool* item);
        void addTool(Tool* item);
        void discard(int quant, int slot);
};

#endif