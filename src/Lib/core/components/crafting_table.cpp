#include "headers/table.hpp"
#include "../globals.hpp"

namespace Lib {

    // IMPLEMENTATION FIELD FOR CHILD CLASS: CraftingTable
    CraftingTable::CraftingTable() : Table(CRAFT_ROWS, CRAFT_COLS){}

    ostream& operator<<(ostream& os, CraftingTable& ct) {
        os << "\nCrafting Table : " << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            os << "[C" << i << " ";
            if (ct.slot[i] == nullptr) {
                os << "-999 0]";
            }
            else {
                os  << (ct.slot[i]->getID()) << " "
                    << (ct.slot[i]->isTool() ?
                        Tool::FromItem(ct.slot[i]).getDurability() :
                        NonTool::FromItem(ct.slot[i]).getQuantity()) << "] ";
            }
            if ((i + 1) % CRAFT_COLS == 0) {
                os << endl;
            }
        }
        return os;
    }

    ostream& operator<<(ostream& os, CraftingTable* ct) {
        int undef_count = CRAFT_SIZE;
        os << "\n[CRAFTING TABLE DETAILS]" << endl;
        os << "Slot" << " | "
            << setw(NUMWIDTH) << "ID" << " | "
            << setw(WIDTH) << "Name" << " | "
            << setw(WIDTH) << "Type" << " | "
            << setw(WIDTH) << "Base Type" << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            if (gm.crftab[i] != nullptr) {
                undef_count--;
                os << setw(NUMWIDTH - to_string(i).length()) << "C" << i << " | ";
                ct->specify(i);
                os << endl;
            }
        }
        if (undef_count == CRAFT_SIZE){
            cout << "No items in crafting table :(" << endl;
        }
        return os;
    }

    void CraftingTable::discard(int qty, int pos) {
        Item* it = this->slot[pos];
        if (it == nullptr)
            return;
        if (it->isTool()) {
            set(pos, nullptr);
        } else if (it->isNonTool()){
            NonTool& nt = NonTool::FromItem(it);
            if (nt.getQuantity() - qty > 0) {
                nt.setQuantity(nt.getQuantity() - qty);
            }
            else if (nt.getQuantity() - qty == 0) {
                set(pos, nullptr);
            }
            else {
                throw new TableException("EMPTY");
            }
        } 
    }

    void CraftingTable::toInv(int slotSrc, int destSlot){
        // Check if there's item in slotSrc from crafting table
        Item* crfItem = gm.crftab[slotSrc];
        if (crfItem == nullptr)
            throw new MoveException("VOID");

        // Copy the item from crafting table
        // Get the item in inventory
        Item* invItem = gm.inv[destSlot];
        if (invItem != nullptr) { // if there's item in inv[destSlot[0]]
            if (invItem->getID() != crfItem->getID()) // if different ID, throw exception.
                throw new MoveException("DIFFTYPE");
            if (crfItem->isNonTool()) {
                // Copy nontool from item inv
                int craft_qty = NonTool::FromItem(crfItem).getQuantity();
                NonTool& item_inv = NonTool::FromItem(gm.inv[destSlot]);
                if (item_inv.getQuantity() + craft_qty > 64) { // Cancel move if quantity maxed out.
                    throw new MoveException("FULL");
                }
                // Set total quantity
                item_inv.setQuantity(item_inv.getQuantity() + craft_qty);
                gm.inv.set(destSlot, invItem->copy());
                gm.crftab.set(slotSrc, nullptr);
                cout << "Item " << invItem->getName() << " successfully moved to the inventory!" << endl;
            }
            else { // should be tool
                throw new MoveException("TOOL");
            }
        }
        else { // dest empty, direct set
            gm.inv.set(destSlot, crfItem->copy());
            gm.crftab.set(slotSrc, nullptr);
            cout << "Item " << crfItem->getName() << " successfully moved to the inventory!" << endl;
        }
    }
}