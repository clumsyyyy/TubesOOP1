#include "headers/table.hpp"
#include "../globals.hpp"

namespace Lib {

    // IMPLEMENTATION FIELD FOR CHILD CLASS: CraftingTable
    /**
     * @brief Construct a new Crafting Table:: Crafting Table object    
     * 
     */
    CraftingTable::CraftingTable() : Table(CRAFT_ROWS, CRAFT_COLS){}

    ostream& operator<<(ostream& os, CraftingTable& ct) {
        os << "Crafting Table : " << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = ct.get(i);
            Item* itemCrf = ct.slot[i];
            os << "[(C" << i << ") "
                << item->getID() << " "
                << item->getName();
            if (itemCrf->getType() == "-") {
                os << " " << itemCrf->getBType();
            }
            if (itemCrf->isTool()) {
                os << " " << itemCrf->getDurability();
            } else if (itemCrf->isNonTool()) {
                os << " " << itemCrf->getQuantity();
            }
            os << "] ";
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
            undef_count--;
            if (gm.crftab[i]->getID() != UNDEFINED_ID){
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
        if (it->isTool()) {
            set(pos, new Item());
        } else if (it->isNonTool()){
            if (it->getQuantity() - qty > 0) {
                it->setQuantity(it->getQuantity() - qty);
            }
            else if (it->getQuantity() - qty == 0) {
                set(pos, new Item());
            }
            else {
                throw new TableException("EMPTY");
            }
        } 
    }

    void CraftingTable::toInv(int slotSrc,int destSlot[]){
        Item* undef_item = new Item();
        Item* item_inv = NULL;
        Item* item_craft = NULL;
        Item* item_moved = NULL;
        Item* crfItem = gm.crftab[slotSrc];
        bool tool = crfItem->isTool();
        if (tool) {
            item_craft = new Tool(*((Tool*)crfItem));
        }
        else {
            item_craft = new NonTool(*((NonTool*)crfItem));
        }

        if (item_craft->getID() == UNDEFINED_ID) {
            throw new MoveException("VOID");
        }
        else {
            item_inv = new Item(*gm.inv[destSlot[0]]);
            bool destKosong = true;
            if (item_inv->getID() != UNDEFINED_ID) {
                destKosong = false;
            }
            if (!destKosong && item_inv->getID() != item_craft->getID()) {
                throw new MoveException("DIFFTYPE");
            }
            if (destKosong) {
                gm.inv.set(destSlot[0], item_craft);
                gm.crftab.set(slotSrc, undef_item);
            }
            else {
                if (!tool) {
                    item_inv = new NonTool(*((NonTool*)gm.inv[destSlot[0]]));
                    if (item_inv->getQuantity() + item_craft->getQuantity() > 64) {
                        throw new MoveException("FULL");
                    }
                    item_inv->setQuantity(item_inv->getQuantity() + item_craft->getQuantity());
                    gm.crftab.set(slotSrc, undef_item);
                    gm.inv.set(destSlot[0], item_inv);
                }
                else {
                    throw new MoveException("TOOL");
                }
            }
        }
    }
}