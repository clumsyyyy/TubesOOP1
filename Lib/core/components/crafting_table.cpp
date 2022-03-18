#include "headers/crafting_table.hpp"

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
            throw "Not valid index\n";
        }
        return this->crftab_buffer[pos];
    }

    void CraftingTable::set(int pos, Item* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw "Not valid index\n";
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
            throw "Not valid index\n";
        }
        (this->crftab_buffer[pos])->displayInfo();
    }

    void CraftingTable::addNonTool(int pos, NonTool* item) {
        if (pos < 0 || pos >= CRAFT_SIZE) {
            throw "Not valid index\n";
        }
    
        if (this->get(pos)->getID() != UNDEFINED_ID) {
            throw "this position has occupation by other item\n";
        } else {
            if (this->get(pos)->getQuantity() + item->getQuantity() > 64) {
                throw "can't add more\nthis position has reach max stack\n";
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
            throw "Not valid index\n";
        }

        if (this->get(pos)->getID() != UNDEFINED_ID) {
            throw "this position has occupation by other item\n";
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
                throw "Not enough items in slot\n";
            }
        } 
    }
}