#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "vars.hpp"
#include "item.hpp"
#include <iostream>

namespace Lib {
    using namespace std;
    class Inventory {
    private:
        Item** inv_buffer;
    public:
        Inventory();
        ~Inventory();
        Item* get(int pos);
        void set(int pos, Item* item);
        void specify(int pos);
        void displayMenu();
        void displayDetails();
        void addNonTool(NonTool* item, int start);
        void addTool(Tool* item, int quant);
        void discard(int quant, int slot);
    };
}

#endif