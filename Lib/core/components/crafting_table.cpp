#include "headers/crafting_table.hpp"
#include "../globals.hpp"

namespace Lib {
    CraftingTable::CraftingTable() {
        this->crftab_buffer = new Item * [CRAFT_COLS * CRAFT_ROWS];
        for (int i = 0; i < CRAFT_COLS * CRAFT_ROWS; i++) {
            this->crftab_buffer[i] = nullptr;
        }
    }

    CraftingTable::~CraftingTable() {
        delete[] this->crftab_buffer;
    }

    Item* CraftingTable::get(int pos) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        }
        return this->crftab_buffer[pos];
    }

    Item* CraftingTable::operator[](int pos) {
        return get(pos);
    }

    void CraftingTable::set(int pos, Item* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        } 
        this->crftab_buffer[pos] = item;
    }

    ostream& operator<<(ostream& os, CraftingTable* ct) {
        os << "Crafting Table : " << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = ct->get(i);
            Item* itemCrf = ct->crftab_buffer[i];
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

    ostream& operator<<(ostream& os, CraftingTable& ct) {
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
                ct.specify(i);
                os << endl;
            }
        }
        if (undef_count == CRAFT_SIZE){
            cout << "No items in crafting table :(" << endl;
        }
        return os;
    }

    void CraftingTable::specify(int pos) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        }
        crftab_buffer[pos]->displayInfo();
    }

    void CraftingTable::addNonTool(int pos, NonTool* item) {
        Item* it = this->get(pos);
        if (it->getID() != UNDEFINED_ID) {
            throw new TableException("OCCUPIED");
        } else {
            if (it->getQuantity() + item->getQuantity() > 64) {
                throw new TableException("FULL");
            } else {
                it->setQuantity(item->getQuantity() + it->getQuantity());
                cout << "set item " << it->getID() << " to C" << pos << endl;
            }
        }
    }

    void CraftingTable::addTool(int pos, Tool* item) {
        Item* it = this->get(pos);
        if (it->getID() != UNDEFINED_ID) {
            throw new TableException("OCCUPIED");
        } else {
            set(pos, item);
            cout << "set item " << item->getID() << " to C" << pos << endl;
        }
            
    }    

    void CraftingTable::discard(int quant, int slot) {
        Item* it = this->crftab_buffer[slot];
        if (it->isTool()) {
            set(slot, new Item());
        } else if (it->isNonTool()){
            if (it->getQuantity() - quant > 0) {
                it->setQuantity(it->getQuantity() - quant);
            }
            else if (it->getQuantity() - quant == 0) {
                set(slot, new Item());
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