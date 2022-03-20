#include "headers/inventory.hpp"
#include "../globals.hpp"

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

    Item* Inventory::get(int pos) {
        if (pos < 0 || pos >= INV_SIZE) {
            throw new InvException("INVALID");
        }
        return this->inv_buffer[pos];
    }

    //Item* Inventory::operator[](int pos) {
    //    if (pos < 0 || pos >= INV_SIZE) {
    //        throw new InvException("INVALID");
    //    }
    //    return this->inv_buffer[pos];
    //}

    void Inventory::set(int pos, Item* item) {
        if (pos < 0 || pos >= INV_SIZE) {
            throw new InvException("INVALID");
        }
        (this->inv_buffer[pos]) = item;
    };

    ostream& operator<<(ostream& os, Inventory* inven) {
        os << "\nInventory: " << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            os << "[I" << i << " "
                << (inven->inv_buffer[i])->getID() << " "
                << (inven->inv_buffer[i])->getQuantity() << " "
                << (inven->inv_buffer[i])->getDurability() << "] ";
            if ((i + 1) % INV_COLS == 0) {
                os << endl;
            }
        }
        return os;
    }

    ostream& operator<<(ostream& os, Inventory& inven) {
        os << "Slot" << " | "
            << setw(NUMWIDTH) << "ID" << " | "
            << setw(WIDTH) << "Name" << " | "
            << setw(WIDTH) << "Type" << " | "
            << setw(WIDTH) << "Base Type" << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            os << setw(NUMWIDTH - to_string(i).length()) << "I" << i << " | ";
            inven.specify(i);
            os << endl;
        }
        return os;
    }

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
                    return;
                }
            }
        }
        // case 2: if not found, find from the first slot
        for (int i = start; i < INV_SIZE; i++){
            if (this->get(i)->getID() == UNDEFINED_ID) {
                if (item->getQuantity() <= MAX_STACK) {
                    this->set(i, item);
                    cout << "Set item " << item->getID() << " to I" << i << endl;
                    return;
                }
                else {
                    NonTool* temp = new NonTool(*item);
                    temp->setQuantity(MAX_STACK);
                    this->set(i, temp);
                    cout << "Set item " << temp->getID() << " to I" << i << endl;
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
                throw new InvException("FULL");
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
            throw new InvException("EMPTY");
        }
    }

    void Inventory::toCraft(int slotSrc,int destSlot[], int N){
        Item* undef_item = new Item();
        Item* item_inv = NULL;
        Item* item_craft = NULL;
        Item* item_moved = NULL;
        bool tool = inv->get(slotSrc)->getBType() == "TOOL";
        if (tool) {
            item_inv = new Tool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getDurability());
        }
        else {
            item_inv = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
        }
        if (item_inv->getID() == UNDEFINED_ID) {
            throw new MoveException("VOID");
        }
        else {
            if (!tool) {
                if (N > item_inv->getQuantity()) {
                    throw new MoveException("NOTENOUGH");
                }
                else {
                    item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                    item_moved->setQuantity(1);

                    for (int i = 0; i < N; i++) {
                        item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                        item_moved->setQuantity(1);
                        item_craft = new NonTool(crftab->get(destSlot[i])->getID(), crftab->get(destSlot[i])->getName(), crftab->get(destSlot[i])->getType(), crftab->get(destSlot[i])->getBType(), crftab->get(destSlot[i])->getQuantity());
                        if (item_craft->getID() != UNDEFINED_ID && item_craft->getID() != item_moved->getID()) {
                            throw new MoveException("DIFFTYPE");
                        }
                        else if (item_craft->getID() == UNDEFINED_ID) {
                            crftab->set(destSlot[i], item_moved);
                        }
                        else {
                            crftab->get(destSlot[i])->setQuantity(crftab->get(destSlot[i])->getQuantity() + 1);
                        }
                    }
                    if (item_inv->getQuantity() - N == 0) {
                        inv->set(slotSrc, undef_item);
                    }
                    else {
                        item_inv->setQuantity(item_inv->getQuantity() - N);
                        inv->set(slotSrc, item_inv);
                    }
                }
            }
            else {
                Item* item_craft = new Item(*crftab->get(destSlot[0]));
                if (item_craft->getID() != UNDEFINED_ID) {
                    throw new MoveException("TOOL");
                }
                else {
                    Tool* item_moved = new Tool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getDurability());
                    inv->set(slotSrc, undef_item);
                    crftab->set(destSlot[0], item_moved);
                }
            }
        }
    }

    void Inventory::toAnotherSlot(int slotSrc,int destSlot[]){
        Item* undef_item = new Item();
        Item* item_inv = NULL;
        Item* item_craft = NULL;
        Item* item_moved = NULL;
        Item* item_inv2 = NULL;
        item_inv2 = new Item(*inv->get(destSlot[0]));
        bool destKosong = true;
        bool tool = inv->get(slotSrc)->getBType() == "TOOL";
        if (tool) {
            item_inv = new Tool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getDurability());
        }
        else {
            item_inv = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
        }
        if (item_inv->getID() == UNDEFINED_ID) {
            throw new MoveException("VOID");
        }
        if (item_inv2->getID() != UNDEFINED_ID) {
            destKosong = false;
        }
        if (!destKosong && item_inv2->getID() != item_inv->getID()) {
            throw new MoveException("DIFFTYPE");
        }
        if (destKosong) {
            inv->set(destSlot[0], item_inv);
            inv->set(slotSrc, undef_item);
        }
        else {
            if (!tool) {
                item_inv2 = new NonTool(inv->get(destSlot[0])->getID(), inv->get(destSlot[0])->getName(), inv->get(destSlot[0])->getType(), inv->get(destSlot[0])->getBType(), inv->get(destSlot[0])->getQuantity());
                int kurang = 64 - item_inv2->getQuantity();
                if (item_inv->getQuantity() > kurang) {
                    item_inv2->setQuantity(64);
                    item_inv->setQuantity(item_inv->getQuantity() - kurang);
                    inv->set(slotSrc, item_inv);
                    inv->set(destSlot[0], item_inv2);
                }
                else {
                    item_inv2->setQuantity(item_inv2->getQuantity() + item_inv->getQuantity());
                    inv->set(slotSrc, undef_item);
                    inv->set(destSlot[0], item_inv2);
                }
            }
            else {
                throw new MoveException("TOOL");
            }

        }
    }        
}