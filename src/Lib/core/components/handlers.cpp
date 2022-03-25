#include "headers/handlers.hpp"
#include "headers/vars.hpp"
#include "headers/exception.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"
#include <limits>
#include <fstream>
#include <iostream>

namespace Lib {

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


    void GiveHandler(string name, int qty) {
        try {
            GiveChecker(name, qty);
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }
    }

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
                            gm.inv.addNonTool(new NonTool(tup, qty), 0);
                        }
                    }
                    else { // Checking if the item is a tool
                        if (qty > (INV_SIZE - gm.inv.filledSlots())) {
                            throw new AddException("TOOL", "OVERCAP");
                        }
                        else {
                            gm.inv.addTool(new Tool(tup, 10), qty);
                        }
                    }
                    return;
                }
            }
            if (!found)
                throw new AddException(name, "INVALID");
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }

    }


    void DiscardHandler(int index, int qty) {
        try {
            Item* it = gm.inv[index];
            if (it == nullptr) {
                throw new InvException("EMPTY");
            }
            else {
                if (it->isNonTool()) { // Checking if the item is NonTool 
                    string nameNT = it->getName();
                    gm.inv.discard(index, qty); // If the item is NonTool, discard by quantity
                    cout << "Discarded item " << nameNT << " from slot I" << index << "." << endl;
                    
                } else {
                    string nameTool = it->getName();
                    gm.inv.set(index, nullptr); // If the item is Tool, discard by setting the slot to empty
                    cout << "Discarded tool " << nameTool << " from slot I" << index << "." << endl;
                    
                }
            }
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }
    }

    void UseHandler(string slot) {
        try {
            int index = -1;
            try {
                index = stoi(slot.substr(1, slot.length() - 1));
            }
            catch (...) {
                index = -1;
            }
            Item* used_item = gm.inv[index];
            if (used_item != nullptr) {
                if (used_item->isNonTool()) // Item can't be used unless it's a tool
                    throw new UseException(used_item->getName());
                else {
                    Tool& t = Tool::FromItem(used_item);
                    t.useItem();
                    if (t.getDurability() == 0) // If the tool durability is 0 after being used, discard the item
                        gm.inv.set(index, nullptr);
                }
            }
            else
                throw new InvException("EMPTY");
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }

    }

    void CraftingHandler() {
        try {
            Crafting::crafting_proses();
        }
        catch (BaseException* exc) {
            exc->printMessage();
        }
    }


    void MoveHandler(string source, int slotCount, vector<string> slotDestV) {
        if (slotCount < 1) {
            throw new MoveException("INVALIDSLOT");
        }
        char src = 'F';
        int slotSrc = -99;
        // get source
        try{
            src = source[0];;
            string source1 = source;
            source1.erase(0, 1);
            slotSrc = stoi(source1);
        }catch(...){
            throw new MoveException("INVALIDSLOTCOMMAND");
        }
        
        if (src != 'C' && src != 'I') {  //Checking validity of source slot
            throw new MoveException("INVALID");
        }

        bool sourceCraft = false;
        if (src == 'C')
            sourceCraft = true;
        if ((sourceCraft && slotSrc >= CRAFT_SIZE) || (!sourceCraft && slotSrc >= INV_SIZE)) {
            throw new MoveException("INVALID");
        }

        Item* it = sourceCraft ? gm.crftab[slotSrc] : gm.inv[slotSrc];

        if (it != nullptr && it->isTool() && slotCount != 1) {
            throw new MoveException("INVALIDSLOT");
        }
        if(sourceCraft && slotCount != 1){
            throw new MoveException("INVALIDSLOT");
        }

        //INPUT DESTINATION SLOT
        string slotDest;
        int* allSlot = new int[slotCount];
        bool toInv = false, toCraft = false;
        for (int i = 0; i < slotCount;i++) {
            slotDest = slotDestV[i];
            if (slotDest[0] == 'C')
                toCraft = true;
            else if (slotDest[0] == 'I')
                toInv = true;
            else
                throw new MoveException("INVALIDDEST");
            // if there's destination in two table (inventory and crafting), throw exception
            if (toInv && toCraft)
                throw new MoveException("DOUBLETYPEDEST");

            slotDest.erase(0, 1);
            try{
                allSlot[i] = stoi(slotDest);
            }catch(...){
                throw new MoveException("INVALIDSLOTCOMMAND");
            }
            
            if ((toCraft && allSlot[i] >= CRAFT_SIZE) || (toInv && allSlot[i] >= INV_SIZE))
                throw new MoveException("INVALIDDEST");
        }

        if (!sourceCraft && toInv && slotCount != 1)
            throw new MoveException("MOVETO2INV");

        try {
            MoveItemHandler(source, slotCount, allSlot, toInv);
        } catch(MoveException* err) {
            throw err;
        }
    }

    void MoveItemHandler(string sourceSlot,int N, int destSlot[], bool destInv){
        char src = sourceSlot[0];
        sourceSlot.erase(0, 1);
        int slotSrc = stoi(sourceSlot);
        //PROSES PEMINDAHAN BARANG DARI CRAFTING TABLE
        if (src == 'I') { //KASUS KETIKA BARANG BERASAL DARI INVENTORY
            if (destInv)
                gm.inv.toAnotherSlot(slotSrc, destSlot[0]);
            else
                gm.inv.toCraft(slotSrc, destSlot, N);
        } else { //KASUS KETIKA BARANG BERASAL DARI CRAFTING TABLE
            if (destInv)
                gm.crftab.toInv(slotSrc, destSlot[0]);
            else
                throw new MoveException("CRAFTTOCRAFT");
        }
        
    }

    void ExportHandler(string path) {
        ofstream outputFile(path);
        for (int i = 0; i < 27; i++) {
            Item* it = gm.inv[i];
            if (it == nullptr)
                outputFile << "0:0" << endl;
            else {
                if (it->isNonTool())
                    outputFile << it->getID() << ":" << NonTool::FromItem(it).getQuantity() << endl;
                else
                    outputFile << it->getID() << ":" << Tool::FromItem(it).getDurability() << endl;
            }
        }
        cout << "Exported file to path " << path << "!" << endl;
        outputFile.close();
    }

    void ClearBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}