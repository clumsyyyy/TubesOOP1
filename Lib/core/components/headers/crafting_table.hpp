#ifndef CRAFTING_TABLE_HPP
#define CRAFTING_TABLE_HPP

#include "vars.hpp"
#include "item.hpp"
#include <iostream>

namespace Lib {
    using namespace std;
    class CraftingTable {
    private:
        Item** crftab_buffer;
    public:
        CraftingTable();
        ~CraftingTable();
        Item* get(int pos);
        void set(int pos, Item* item);
        void specify(int pos);
        void displayMenu();
        void displayDetails();
        void addNonTool(int pos, NonTool* item);
        void addTool(int pos, Tool* item);
        void discard(int quant, int slot);
    };
}

#endif