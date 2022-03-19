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
        friend ostream& operator<<(ostream& os, Inventory* inven);
        friend ostream& operator<<(ostream& os, Inventory& inven);
        void displayMenu();
        void displayDetails();
        void addNonTool(NonTool* item, int start);
        void addTool(Tool* item, int quant);
        void discard(int quant, int slot);
        void toCraft(int slotSrc,int destSlot[], int N);
        void toAnotherSlot(int slotSrc,int destSlot[]);
        //friend ostream& operator << (ostream& out, const Inventory& inv) {
        //    out << "Inventory: ";
        //    for (int i = 0; i < INV_SIZE; i++) {
        //        out << "[I" << i << " "
        //            << (inv.inv_buffer[i])->getID() << " "
        //            << (inv.inv_buffer[i])->getQuantity() << " "
        //            << (inv.inv_buffer[i])->getDurability() << "] ";
        //        if ((i + 1) % INV_COLS == 0) {
        //            out << endl;
        //        }

        //    }
        //    return out;
        //}
    };
}

#endif