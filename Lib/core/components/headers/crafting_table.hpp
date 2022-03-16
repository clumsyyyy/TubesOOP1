#ifndef CRAFTING_TABLE_HPP
#define CRAFTING_TABLE_HPP

#include "vars.hpp"
#include "item.hpp"
#include <iostream>
using namespace std;

class CraftingTable {
    private:
        Item** crftab_buffer;
    public:
        CraftingTable();
        ~CraftingTable();
        Item* get(int pos);
        void set(int pos, Item* item);
        void specify(int i, int j);
        void displayMenu();
        void displayDetails();
        void addNonTool(NonTool* item);
        void addTool(Tool* item);
        void discard(int quant, int slot);
};

#endif