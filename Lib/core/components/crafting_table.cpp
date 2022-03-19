#include "headers/crafting_table.hpp"
#include "../globals.hpp"

namespace Lib {
    CraftingTable::CraftingTable() {
        this->crftab_buffer = new Item * [CRAFT_COLS * CRAFT_ROWS];
        for (int i = 0; i < CRAFT_COLS * CRAFT_ROWS; i++) {
            this->crftab_buffer[i] = new Item();
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

    void CraftingTable::set(int pos, Item* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        } 
        this->crftab_buffer[pos] = item;
    }

    void CraftingTable::displayMenu() {
        cout << "Crafting Table : " << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            cout << "[(C" << i << ") "
                << this->crftab_buffer[i]->getID() << " "
                << this->crftab_buffer[i]->getName();
            if (this->crftab_buffer[i]->getType() == "-") {
                cout << " " << this->crftab_buffer[i]->getBType();
            }
            if (this->crftab_buffer[i]->getBType() == "TOOL") {
                cout << " " << this->crftab_buffer[i]->getDurability();
            } else if (this->crftab_buffer[i]->getBType() == "NONTOOL") {
                cout << " " << this->crftab_buffer[i]->getQuantity();
            }
            cout << "] ";
            if ((i + 1) % CRAFT_COLS == 0) {
                cout << endl;
            }
        }
    }

    void CraftingTable::displayDetails() {
        cout << "Slot" << " | "
            << setw(NUMWIDTH) << "ID" << " | "
            << setw(WIDTH) << "Name" << " | "
            << setw(WIDTH) << "Type" << " | "
            << setw(WIDTH) << "Base Type" << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            cout << setw(NUMWIDTH - to_string(i).length()) << "I" << i << " | ";
            this->specify(i);
            cout << endl;
        }
    };

    void CraftingTable::specify(int pos) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        }
        (this->crftab_buffer[pos])->displayInfo();
    }

    void CraftingTable::addNonTool(int pos, NonTool* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        }
    
        if (this->get(pos)->getID() != UNDEFINED_ID) {
            throw new TableException("OCCUPIED");
        } else {
            if (this->get(pos)->getQuantity() + item->getQuantity() > 64) {
                throw new TableException("FULL");
            } else {
                NonTool *temp = new NonTool(*item);
                temp->setQuantity(item->getQuantity()+this->get(pos)->getQuantity());
                set(pos, temp);
                cout << "set item " << item->getID() << " to C" << pos << endl;
            }
        }
    }

    void CraftingTable::addTool(int pos, Tool* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw new TableException("INVALID");
        }

        if (this->get(pos)->getID() != UNDEFINED_ID) {
            throw new TableException("OCCUPIED");
        } else {
            set(pos, item);
            cout << "set item " << item->getID() << " to C" << pos << endl;
        }
            
    }
    

    void CraftingTable::discard(int quant, int slot) {
        if (this->crftab_buffer[slot]->getBType() == "TOOL") {
            set(slot, new Item());
        } else if (this->crftab_buffer[slot]->getBType() == "NONTOOL"){
            if (this->crftab_buffer[slot]->getQuantity() - quant > 0) {
                this->crftab_buffer[slot]->setQuantity(this->crftab_buffer[slot]->getQuantity() - quant);
            }
            else if (this->crftab_buffer[slot]->getQuantity() - quant == 0) {
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
        bool tool = crftab->get(slotSrc)->getBType() == "TOOL";
        if (tool) {
            item_craft = new Tool(crftab->get(slotSrc)->getID(), crftab->get(slotSrc)->getName(), crftab->get(slotSrc)->getType(), crftab->get(slotSrc)->getBType(), crftab->get(slotSrc)->getDurability());
        }
        else {
            item_craft = new NonTool(crftab->get(slotSrc)->getID(), crftab->get(slotSrc)->getName(), crftab->get(slotSrc)->getType(), crftab->get(slotSrc)->getBType(), crftab->get(slotSrc)->getQuantity());
        }

        if (item_craft->getID() == UNDEFINED_ID) {
            throw new MoveException("VOID");
        }
        else {
            item_inv = new Item(*inv->get(destSlot[0]));
            bool destKosong = true;
            if (item_inv->getID() != UNDEFINED_ID) {
                destKosong = false;
            }
            if (!destKosong && item_inv->getID() != item_craft->getID()) {
                throw new MoveException("DIFFTYPE");
            }
            if (destKosong) {
                inv->set(destSlot[0], item_craft);
                crftab->set(slotSrc, undef_item);
            }
            else {
                if (!tool) {
                    item_inv = new NonTool(inv->get(destSlot[0])->getID(), inv->get(destSlot[0])->getName(), inv->get(destSlot[0])->getType(), inv->get(destSlot[0])->getBType(), inv->get(destSlot[0])->getQuantity());
                    if (item_inv->getQuantity() + item_craft->getQuantity() > 64) {
                        throw new MoveException("FULL");
                    }
                    item_inv->setQuantity(item_inv->getQuantity() + item_craft->getQuantity());
                    crftab->set(slotSrc, undef_item);
                    inv->set(destSlot[0], item_inv);
                }
                else {
                    throw new MoveException("TOOL");
                }
            }
        }
    }
}