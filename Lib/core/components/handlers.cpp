#include "headers/handlers.hpp"
#include "headers/exception.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"
#include <limits>
#include <fstream>
#include <iostream>

namespace Lib {
    /**
     * @brief Show current inventory and crafting table item info
     *  
     * 
     * @param mode "ALL" = show all items, "ITEM" = specific item info
     * @param slot_id Slot ID
     */
    void DetailsHandler(string mode, int slot_id) {
        if (mode == "ALL") { // Showing info for all items
            cout << &(gm.inv);
            cout << &(gm.crftab);
        }
        else if (mode == "ITEM") { // Showing specific item info (by slot)
            gm.inv.specify(slot_id);
            cout << endl;
        }
    }

    /**
     * @brief Invoke GiveChecker to check if the item can be given
     *  
     * 
     * @param name Item Name
     * @param qty Item Quantity
     */
    void GiveHandler(string name, int qty) {
        try {
            GiveChecker(name, qty);
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }
    }

    /**
     * @brief Checking if the item can be given (valid)
     *  Valid when name and quantity of the item are valid 
     *  
     * 
     * @param name Item name
     * @param qty Item quantity
     */
    void GiveChecker(string name, int qty) {
        try {
            bool found = false;
            for (tuple tup : gm.itemConfig) {
                // tup = (ID, name, base_type, type)
                if (get<1>(tup) == name) { // Checking if the item name is valid
                    found = true;
                    if (get<3>(tup) == "NONTOOL") { // Checking if the item is a non-tool
                        if (qty > MAX_STACK * (INV_SIZE - gm.inv.filledSlots())) {
                            throw new AddException("NONTOOL", "OVERCAP");
                        }
                        else {
                            NonTool* NT = new NonTool(tup, qty);
                            gm.inv.addNonTool(NT, 0);
                        }
                    }
                    else { // Checking if the item is a tool
                        if (qty > (INV_SIZE - gm.inv.filledSlots())) {
                            throw new AddException("TOOL", "OVERCAP");
                        }
                        else {
                            Tool* T = new Tool(tup, 10);
                            gm.inv.addTool(T, qty);
                        }
                    }
                    return;
                }
            }
            if (!found) {
                throw new AddException(name, "INVALID");
            }
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }

    }

    /**
     * @brief Discard spesific item from the Inventory
     * 
     * @param slot Inventory slot ID to be discarded
     * @param qty Quantity of the item to be discarded
     */
    void DiscardHandler(int index, int qty) {
        try {
            if (gm.inv[index]->isNonTool()) { // Checking if the item is NonTool 
                gm.inv.discard(index, qty); // If the item is NonTool, discard by quantity
            }
            else if (gm.inv[index]->isTool()) {
                gm.inv.set(index, new Item()); // If the item is Tool, discard by setting the slot to empty
            }
            else if (gm.inv[index]->isUndef()) {
                throw new InvException("EMPTY");
            }
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }
    }

    /**
     * @brief Decrease durability of the tool item by 1
     * 
     * @param slot Inventory slot ID to be used (Must be a tool item)
     */
    void UseHandler(string slot) {
        try {
            int index = stoi(slot.substr(1, slot.length() - 1));
            Item* used_item = gm.inv[index];
            if (used_item->isNonTool()) { // Item can't be used unless it's a tool
                throw new UseException(used_item->getName());
            }
            else {
                if (used_item->getDurability() == 1){ // If the tool durability is 1, after being used, discard the item
                    used_item->useItem();
                    gm.inv.set(index, new Item());
                } else {
                    used_item->useItem();
                }
            }
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }

    }

    /**
     * @brief Invoke crafting_proses to craft the current items in the crafting table
     * 
     */
    void CraftingHandler() {
        Crafting::crafting_proses();
    }

    void ClearBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    /**
     * @brief Moving item from a slot to another slot
     * 
     * @param source 
     * @param slotCount 
     * @param slotDestV 
     */
    void MoveHandler(string source, int slotCount, vector<string> slotDestV) {
        if (slotCount < 1) {
            MoveException::createThenPrintExc("INVALIDSLOT");
            return;
        }
        char src = source[0];
        string source1 = source;
        source1.erase(0, 1);
        int slotSrc = stoi(source1);
        if (src != 'C' && src != 'I') {  //Checking validity of source slot
            MoveException::createThenPrintExc("INVALID");
            return;
        }

        if ((src == 'C' && slotSrc >= CRAFT_SIZE) || (src == 'I' && slotSrc >= INV_SIZE)) {
            MoveException::createThenPrintExc("INVALID");
            return;
        }

        bool sourceCraft = false, sourceInv = false;
        if (src == 'C') {
            sourceCraft = true;
        }
        else {
            sourceInv = true;
        };

        bool tool = false, nontool = false;

        // Checking for item type to be moved
        if (sourceInv && gm.inv[slotSrc]->isTool())
            tool = true;
        else if(sourceInv)
            nontool = true;

        if (sourceCraft && gm.crftab[slotSrc]->isTool())
            tool = true;
        else if(sourceCraft)
            nontool = true;

        if (tool && slotCount != 1) {
            MoveException::createThenPrintExc("INVALIDSLOT");
            return;
        }

        //INPUT DESTINATION SLOT
        string slotDest;
        int* allSlot = new int[slotCount];
        bool bool_inv = false, craft = false;
        for (int i = 0; i < slotCount;i++) {
            slotDest = slotDestV[i];
            if (slotDest[0] == 'C') {
                craft = true;
            }
            else if (slotDest[0] == 'I') {
                bool_inv = true;
            }
            else {
                MoveException::createThenPrintExc("INVALIDDEST");
                return;
            }
            if (bool_inv && craft) {
                MoveException::createThenPrintExc("DOUBLETYPEDEST");
                return;
            }
            slotDest.erase(0, 1);
            allSlot[i] = stoi(slotDest);
            
            if ((craft && allSlot[i] >= CRAFT_SIZE) || (bool_inv && allSlot[i] >= INV_SIZE)) {
                MoveException::createThenPrintExc("INVALIDDEST");
                return;
            }
        }

        if (sourceInv && bool_inv && slotCount != 1) {
            MoveException::createThenPrintExc("MOVETO2INV");
            return;
        }
        try {
            MoveItemHandler(source, slotCount, allSlot, bool_inv);
        } catch(MoveException* err) {
            err->printMessage();
        }
    }

    void MoveItemHandler(string sourceSlot,int N, int destSlot[],bool destInv){
        char src = sourceSlot[0];
        sourceSlot.erase(0, 1);
        int slotSrc = stoi(sourceSlot);
        bool sourceInv = (src == 'I');
        bool sourceCraft = !sourceInv;
        bool craft = !destInv;
        //PROSES PEMINDAHAN BARANG DARI CRAFTING TABLE
        if (sourceCraft) {        //KASUS KETIKA BARANG BERASAL DARI CRAFTING TABLE
            if (craft) {
                throw new MoveException("CRAFTTOCRAFT");
            }else{
                gm.crftab.toInv(slotSrc,destSlot);
            }
        }
        if (sourceInv) {      //KASUS KETIKA BARANG BERASAL DARI INVENTORY
            if (craft) {
                try{
                    gm.inv.toCraft(slotSrc,destSlot,N);
                }catch(MoveException* err){
                    err->printMessage();
                }
            }
            if (destInv) {
                try{
                    gm.inv.toAnotherSlot(slotSrc,destSlot);
                }catch(MoveException* err){
                    err->printMessage();
                }
            }
        }
        
    }
    
    /**
     * @brief Export inventory state to a file
     * 
     * @param path 
     */
    void ExportHandler(string path) {
        ofstream outputFile(path);
        for (int i = 0; i < 27; i++) {
            Item* it = gm.inv[i];
            string type = it->getBType();
            if (type == "NONTOOL") {
                outputFile << it->getID() << ":" << it->getQuantity() << endl;
            }
            else if (type == "TOOL") {
                outputFile << it->getID() << ":" << it->getDurability() << endl;
            }
            else if (type == "UNDEFINED") {
                outputFile << "0:0" << endl;
            }
        }
        cout << "Exported" << endl;
        outputFile.close();
    }
}