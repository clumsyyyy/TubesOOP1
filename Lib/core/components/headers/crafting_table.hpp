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
        bool valid_index(int pos);
        Item* get(int pos);
        void set(int pos, Item* item);
        void specify(int pos);
        friend ostream& operator<<(ostream& os, CraftingTable* ct);
        friend ostream& operator<<(ostream& os, CraftingTable& ct);
        Item* operator[](int pos);
        void discard(int quant, int slot);
        void toInv(int slotSrc,int destSlot[]);
    };
}

#endif