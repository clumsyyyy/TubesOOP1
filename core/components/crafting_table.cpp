#include "headers/crafting_table.hpp"

CraftingTable::CraftingTable() {
    this->crftab_buffer = new Item*[CRAFT_COLS*CRAFT_ROWS];
    for (int i = 0; i < CRAFT_COLS*CRAFT_ROWS; i++) {
        this->crftab_buffer[i] = new Item();
    }  
}

CraftingTable::~CraftingTable() {
    delete[] this->crftab_buffer;
 }

Item CraftingTable::get(int i, int j) {
    return *this->crftab_buffer[i*CRAFT_COLS +j];
}

void CraftingTable::set(int i, int j, Item* item) {
    this->crftab_buffer[i*CRAFT_COLS + j] = item;
}

void CraftingTable::displayMenu() {
    cout << "Crafting Tabel : " << endl;
    for (int i, n = 0; i < CRAFT_ROWS; i++) {
        for (int j = 0; j < CRAFT_COLS; j++) {
            cout << "[(C" << n << ") "
            << this->crftab_buffer[i*CRAFT_COLS + j]->getID() << " "
            << this->crftab_buffer[i*CRAFT_COLS + j]->getQuantity();
            if (this->crftab_buffer[i*CRAFT_COLS + j]->getType() == "Tool") {
                cout << " " << this->crftab_buffer[i*CRAFT_COLS + j]->getDurability(); 
            }
            cout << "] ";
            n++;
        }
        cout << endl;
    }
}

void CraftingTable::addNonTool(NonTool* item) {
    for (int i, n = 0; i < CRAFT_ROWS; i++) {
        for (int j = 0; j < CRAFT_COLS; j++) {
            if (this->get(i,j).getID() == UNDEFINED_ID) {
                if (item->getQuantity() <= MAX_STACK) {
                    this->set(i, j, item);
                    cout << "set item " << item->getID() << "to (C" << n << ")" << endl;
                    break;
                } else {
                    NonTool* temp = new NonTool(*item);
                    temp->setQuantity(MAX_STACK);
                    item->setQuantity(item->getQuantity()-MAX_STACK);
                    this->set(i, j, temp);
                    cout << "set item " << item->getID() << " to (C" << n << ")" << endl;
                    cout << item->getQuantity() << " stack left" << endl;
                }
            } else if (this->get(i,j).getID() == item->getID()) {
                if (this->get(i, j).getQuantity() + item->getQuantity() <= MAX_STACK) {
                    this->get(i, j).setQuantity(this->get(i, j).getQuantity() + item->getQuantity());
                    cout << "item " << item->getID() << " has added to (C" << n << ")" << endl;
                    break;
                } else {
                    NonTool* temp = new NonTool(*item);
                    temp->setQuantity(MAX_STACK);
                    item->setQuantity(item->getQuantity()-(MAX_STACK+this->get(i, j).getQuantity()));
                    this->set(i, j, temp);
                    cout << "item " << item->getID() << " has added to (C" << n << ")" << endl;
                }
            } 
            n++;
        }
    }
}

void CraftingTable::addTool(Tool* item) {
     for (int i, n = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            // base case if no such item exists in inventory
            if (this->get(i, j).getID() == UNDEFINED_ID){
                this->set(i ,j, item);
                cout << "set item " << item->getID() << " to (C" << n << ")" << endl;
                break;
            }
            n++;
        }
    }    
}

void CraftingTable::discard(int quant, int slot) {
    if (this->crftab_buffer[slot]->getQuantity() - quant >= 0){
        this->crftab_buffer[slot]->setQuantity(this->crftab_buffer[slot]->getQuantity() - quant);
    } else {
        cout << "Not enough items in slot" << endl;
    }
}