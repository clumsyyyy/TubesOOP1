#include "headers/table.hpp"
#include "../globals.hpp"

namespace Lib {

    // IMPLEMENTATION FIELD FOR CHILD CLASS: Inventory
    Inventory::Inventory() : Table(INV_ROWS, INV_COLS){}

    ostream& operator<<(ostream& os, Inventory& inven) {
        os << "\nInventory: " << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            os << "[I" << i << " ";
            if (inven.slot[i] == nullptr) {
                os << "-999 0]";
            }
            else {
                os  << (inven.slot[i]->getID()) << " "
                    << (inven.slot[i]->isTool() ?
                        Tool::FromItem(inven.slot[i]).getDurability() :
                        NonTool::FromItem(inven.slot[i]).getQuantity()) << "] ";
            }
            if ((i + 1) % INV_COLS == 0) {
                os << endl;
            }
        }
        return os;
    }

    /**
     * @brief Overload the << operator to display inventory details
     * 
     * @param os Output Stream
     * @param inven inventory to be displayed details
     * @return ostream& reference to the output stream
     */
    ostream& operator<<(ostream& os, Inventory* inven) {
        int undef_count = INV_SIZE;
        os << "\n\n[INVENTORY DETAILS]" << endl;
        os << "Slot" << " | "
            << setw(NUMWIDTH) << "ID" << " | "
            << setw(WIDTH) << "Name" << " | "
            << setw(WIDTH) << "Type" << " | "
            << setw(WIDTH) << "Base Type" << endl;
        for (int i = 0; i < INV_SIZE; i++) {
            if (inven->slot[i] != nullptr) {
                undef_count--;
                os << setw(NUMWIDTH - to_string(i).length()) << "I" << i << " | ";
                inven->specify(i);
                os << endl;
            }
        }
        if (undef_count == INV_SIZE){
            os << "\nNo items in inventory :(" << endl;
        }
        return os;
    }

    /**
     * @brief Returns the number of filled slots in the inventory
     *
     * @return The number of filled slots
     */
    int Inventory::filledSlots() {
        int count = 0;
        while (this->get(count) != nullptr) {
            count++;
        }
        return count;
    }

    /**
     * @brief Adds a non-tool item to the inventory
     *
     * @param item item to be added
     * @param start start index to begin adding
     */
    void Inventory::addNonTool(NonTool* item, int start){
        int emptyCount = 0;
        for (int i = start; i < INV_SIZE; i++) {
            if (this->get(i) != nullptr) {
                NonTool& currItem = NonTool::FromItem(this->get(i));
                // case 1: other item exists (stackable)
                if (currItem.getID() == item->getID()) {
                    // if current slot less than max stack, increase quantity
                    if (currItem.getQuantity() + item->getQuantity() <= MAX_STACK) {
                        currItem.setQuantity(currItem.getQuantity() + item->getQuantity());
                        cout << "Item " << item->getName() << " successfully added!" << endl;
                        return;
                    }
                    else {
                        if (emptyCount == 0) {
                            item->setQuantity(item->getQuantity() - (MAX_STACK - currItem.getQuantity()));
                            currItem.setQuantity(MAX_STACK);
                            this->addNonTool(item, i + 1);
                            return;
                        }
                        else {
                            for (int j = 0; j < INV_SIZE && emptyCount != 0; j++) {
                                if (this->get(j) == nullptr && item->getQuantity() > MAX_STACK) {
                                    emptyCount--;
                                    NonTool* NT = new NonTool(*item);
                                    NT->setQuantity(MAX_STACK);
                                    this->set(j, NT);
                                    item->setQuantity(item->getQuantity() - MAX_STACK);
                                }
                            }
                            if (currItem.getQuantity() + item->getQuantity() <= MAX_STACK) {
                                currItem.setQuantity(currItem.getQuantity() + item->getQuantity());
                                cout << "Item " << item->getName() << " successfully added!" << endl;
                                return;
                            }
                            else {
                                item->setQuantity(item->getQuantity() - (MAX_STACK - currItem.getQuantity()));
                                currItem.setQuantity(MAX_STACK);
                                this->addNonTool(item, i + 1);
                                return;
                            }
                        }
                    }
                }
            }
            else {
                emptyCount++;
            }
        }
        // case 2: if not found, find from the first slot
        for (int i = 0; i < INV_SIZE; i++){
            if (this->get(i) == nullptr) {
                if (item->getQuantity() <= MAX_STACK) {
                    this->set(i, item);
                    cout << "Item " << item->getName() << " successfully added!" << endl;
                    return;
                }
                else {
                    NonTool* NT = new NonTool(*item);
                    NT->setQuantity(MAX_STACK);
                    this->set(i, NT);
                    item->setQuantity(item->getQuantity() - MAX_STACK);
                    continue;
                }
            }
        }
    }

    /**
     * @brief Adds a tool item to the inventory
     *
     * @param item item to be added
     * @param quant quantity of the item
     */
    void Inventory::addTool(Tool* item, int qty){
        bool added = false;
        Tool* temp;
        for (int i = 0; i < qty; i++) {
            temp = new Tool(*item);
            added = false;
            for (int j = 0; j < INV_SIZE; j++) {
                // base case if no such item exists in inventory
                if (this->get(j) == nullptr) {
                    this->set(j, temp);
                    added = true;
                    break;
                }
            }
            if (!added) {
                delete temp;
                throw new InvException("FULL");
            }
        }
        cout << "Tool " << item->getName() << " successfully added!" << endl;
    }

     /**
     * @brief Discards an item from a slot in the inventory. Prereq: slot[index] is NonTool and NOT NULL.
     *
     * @param index the destination index to be discarded
     * @param qty quantity of the item
     */
    void Inventory::discard(int index, int qty) {
        NonTool& target = NonTool::FromItem(this->slot[index]);
        if (target.getQuantity() - qty > 0)
            target.setQuantity(target.getQuantity() - qty);
        else if (target.getQuantity() - qty == 0)
            set(index, nullptr);
        else
            throw new InvException("OVER");
    }

    void Inventory::toCraft(int slotSrc, int destSlot[], int N){
        Item* itInv = gm.inv[slotSrc];
        if (itInv == nullptr)
            throw new MoveException("VOID");
        bool tool = itInv->isTool();
        if (!tool) { // if item source is nontool
            NonTool& inv = NonTool::FromItem(itInv);
            if (N > inv.getQuantity()) // Check if quantity is enough to dest
                throw new MoveException("NOTENOUGH");
            for (int i = 0; i < N; i++) { // For all destination
                Item* it = gm.crftab[destSlot[i]];
                if (it != nullptr && it->getID() != inv.getID()) {
                    // If there's already a nontool with different id than inv, throw error
                    throw new MoveException("DIFFTYPE");
                }
                if (it == nullptr) { // If no item in dest, copy and set qty to 1
                    NonTool* newItem = new NonTool(inv);
                    newItem->setQuantity(1);
                    gm.crftab.set(destSlot[i], newItem);
                }
                else { // If there's item in dest with same ID, add the qty in crafting
                    NonTool& crf = NonTool::FromItem(it);
                    crf.setQuantity(crf.getQuantity() + 1);
                }
            }
            // Before get nulled (maybe), we print it first.
            cout << "Item " << inv.getName() << " successfully moved to the crafting table!" << endl;
            if (inv.getQuantity() == N) // If move all of them, set to null
                gm.inv.set(slotSrc, nullptr);
            else // If move some of them, just set the quantity.
                inv.setQuantity(inv.getQuantity() - N);
        }
        else { // If item source is tool
            Item* item_craft = gm.crftab[destSlot[0]];
            if (item_craft != nullptr) // if destination already has tool
                throw new MoveException("TOOL");
            else { // if destination empty, copy and move it to crafting table
                // before null'd, we cout it first
                cout << "Tool " << itInv->getName() << " successfully moved to the crafting table!" << endl;
                gm.crftab.set(destSlot[0], itInv->copy());
                gm.inv.set(slotSrc, nullptr);
            }
        }
    }

    void Inventory::toAnotherSlot(int slotSrc, int destSlot){
        Item* itInv = gm.inv[slotSrc];
        if (itInv == nullptr) { // if source is null, throw error
            throw new MoveException("VOID");
        }
        // itInv / source should not null here
        Item* itInv2 = gm.inv[destSlot];
        if (itInv2 == nullptr) { // if dest empty, copy to dest and set empty source
            gm.inv.set(destSlot, itInv->copy());
            gm.inv.set(slotSrc, nullptr);
            cout << "Item " << itInv->getName() << " successfully moved to the inventory!" << endl;
            return;
        }
        else if (itInv->getID() != itInv2->getID()) { // if dest not empty throw error
            throw new MoveException("DIFFTYPE");
        }
        // dest not empty and src.id == dest.id
        if (!itInv->isTool()) { // if nontool, we proceed
            NonTool& ntSrc = NonTool::FromItem(itInv);
            NonTool& ntDest = NonTool::FromItem(itInv2);
            int destQtyLeft = 64 - ntDest.getQuantity();
            if (ntSrc.getQuantity() > destQtyLeft) { // if there's no qty left (some src moved), we adjust the qty.
                ntDest.setQuantity(MAX_STACK);
                ntSrc.setQuantity(ntSrc.getQuantity() - destQtyLeft);
            }
            else { // if there's qty left in dest (all src moved), we empty the src
                ntDest.setQuantity(ntDest.getQuantity() + ntSrc.getQuantity());
                gm.inv.set(slotSrc, nullptr);
            }
            cout << "Item " << ntDest.getName() << " successfully moved to another slot!" << endl;
        }
        else { // if src is tool, throw error
            throw new MoveException("TOOL");
        }
    }        
}