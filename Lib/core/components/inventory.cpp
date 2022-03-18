#include "headers/inventory.hpp"

namespace Lib {
    Inventory::Inventory() {
        this->inv_buffer = new Item * [INV_ROWS * INV_COLS];
        for (int i = 0; i < INV_ROWS * INV_COLS; i++) {
            this->inv_buffer[i] = new Item();
        }
    }

    Inventory::~Inventory() {
        delete[] this->inv_buffer;
    }

Item* Inventory::get(int pos){
    return this->inv_buffer[pos] ;
}

    void Inventory::set(int pos, Item* item) {
        (this->inv_buffer[pos]) = item;
    };

    void Inventory::displayMenu() {
        cout << "\nInventory: " << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            cout << "[I" << i << " "
                << (this->inv_buffer[i])->getID() << " "
                << (this->inv_buffer[i])->getQuantity() << " "
                << (this->inv_buffer[i])->getDurability() << "] ";
            if ((i + 1) % INV_COLS == 0) {
                cout << endl;
            }

        }
    };

    void Inventory::displayDetails() {
        cout << "Slot" << " | "
            << setw(NUMWIDTH) << "ID" << " | "
            << setw(WIDTH) << "Name" << " | "
            << setw(WIDTH) << "Type" << " | "
            << setw(WIDTH) << "Base Type" << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            cout << setw(NUMWIDTH - to_string(i).length()) << "I" << i << " | ";
            this->specify(i);
            cout << endl;
        }
    };

    void Inventory::specify(int pos) {
        (this->inv_buffer[pos])->displayInfo();
    }

void Inventory::addNonTool(NonTool* item, int start){
    for (int i = start; i < INV_SIZE; i++) {
        // case 1: other item exists (stackable)
        if (this->get(i)->getID() == item->getID()) {
            // if current slot less than max stack, increase quantity
            if (this->get(i)->getQuantity() + item->getQuantity() <= MAX_STACK) {
                this->get(i)->setQuantity(this->get(i)->getQuantity() + item->getQuantity());
                return;
            }
            else {
                item->setQuantity(item->getQuantity() - (MAX_STACK - this->get(i)->getQuantity()));
                cout << "Stacked item, " << item->getQuantity() << " left" << endl;
                this->get(i)->setQuantity(MAX_STACK);
                this->addNonTool(item, i + 1);
            }
        }
    }
    // case 2: if not found, find from the first slot
    for (int i = 0; i < INV_SIZE; i++){
        if (this->get(i)->getID() == UNDEFINED_ID) {
            if (item->getQuantity() <= MAX_STACK) {
                this->set(i, item);
                cout << "set item " << item->getID() << " to I" << i << endl;
                return;
            }
            else {
                NonTool* temp = new NonTool(*item);
                temp->setQuantity(MAX_STACK);
                this->set(i, temp);
                cout << "set item " << temp->getID() << " to I" << i << endl;
                cout << item->getQuantity() << " stacks left" << endl;
                item->setQuantity(item->getQuantity() - MAX_STACK);
                continue;
            }
        }
    }
    return;
}

void Inventory::addTool(Tool* item, int quant){
    bool added = false;
    for (int j = 0; j < quant; j++) {
        added = false;
        for (int i = 0; i < INV_SIZE; i++) {
            // base case if no such item exists in inventory
            if (this->get(i)->getID() == UNDEFINED_ID) {
                this->set(i, item);
                added = true;
                cout << "set item " << item->getID() << " to I" << i << endl;
                break;
            }
        }
        if (!added) {
            cout << "inventory full!" << endl;
            return;
        }
    }
     
}

    void Inventory::discard(int quant, int slot) {
        if (this->inv_buffer[slot]->getQuantity() - quant > 0) {
            this->inv_buffer[slot]->setQuantity(this->inv_buffer[slot]->getQuantity() - quant);
        }
        else if (this->inv_buffer[slot]->getQuantity() - quant == 0) {
            set(slot, new Item());
        }
        else {
            cout << "Not enough items in slot" << endl;
        }
    }
}