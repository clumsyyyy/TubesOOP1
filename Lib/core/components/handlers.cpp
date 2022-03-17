#include "headers/handlers.hpp"
#include "../globals.hpp"
#include <limits>

namespace Lib {
    void DetailsHandler() {
        string mode;
        cin >> mode;
        if (mode == "ALL") {
            inv->displayDetails();
            crftab->displayDetails();
        }
        else if (mode == "ITEM") {
            int i;
            cin >> i;
            inv->specify(i);
            cout << endl;
        }
    }

    void GiveHandler() {
        string name;
        int temp;
        cin >> name >> temp;
        GiveChecker(name, temp);
    }

    void GiveChecker(string name, int temp) {
        for (tuple tup : *itemConfig) {
            if (get<1>(tup) == name) {
                if (get<3>(tup) == "NONTOOL") {
                    NonTool* NT = new NonTool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                    inv->addNonTool(NT, 0);
                    break;
                }
                else {
                    Tool* T = new Tool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                    inv->addTool(T);
                    break;
                }
            }
            else {
                //throw exception here
            }
        }
    }

    void DiscardHandler() {
        string slot;
        int quant;
        cin >> slot >> quant;
        int index = stoi(slot.substr(1, slot.length() - 1));
        if (inv->get(index)->getBType() == "NONTOOL") {
            inv->discard(quant, index);
        }
        else {
            inv->set(index, new Item());
        }
    }

    void CraftingHandler() {
        for (tuple tup : *recipeConfig) {
            int sum = 0;
            int min = 0;
            string name;
            Crafting crf(tup);
            crf.recipe();
            name = crf.getName();
            sum = crf.getSum();
            if (sum > 0) {
                GiveChecker(name, sum);
                cout << "crafted " << sum << " " << name << endl;
                crf.returning();
                return;
            }
        }
        Crafting crf;
        int durability = crf.tools();
        int sum = crf.getSum();
        string name = crf.getName();

        if (sum == 2) {
            for (int i = 0; i < CRAFT_SIZE; i++) {
                if (crftab->get(i)->getName() == name) {
                    crftab->get(i)->setQuantity(crftab->get(i)->getQuantity() - 1);
                }

            }
            GiveChecker(name, durability);
            crf.returning();
        }
        else {
            throw "Recipe not found\n";
        }
    }

    void ClearBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

	bool isToolMoved(int slot, bool invSource){
        if(invSource){
            return inv->get(slot)->getBType() == "TOOL";
        }else{
            return crftab->get(slot)->getBType() == "TOOL";
        }
    };
	bool isInv(char a){
        return a == 'I';        
    };

    void MoveHandler(string source, int slotCount) {
        string err = "";

        if (slotCount < 1) {
            err = "Invalid slot count\n";
            throw err;
        }

        char src = source[0];
        string source1 = source;
        source1.erase(0, 1);
        int slotSrc = stoi(source1);
        if (src != 'C' && src != 'I') {           //CHECKING SOURCE SLOT APAKAH VALID ATO TIDAK
            ClearBuffer();
            err = "You move an invalid slot!\n";
            throw err;
        }

        if ((src == 'C' && slotSrc >= CRAFT_SIZE) || (src == 'I' && slotSrc >= INV_SIZE)) {
            ClearBuffer();
            err = "You move an invalid slot!\n";
            throw err;
        }

        bool sourceCraft = false, sourceInv = false;
        if (src == 'C') {
            sourceCraft = true;
        }
        else {
            sourceInv = true;
        };

        bool tool = false, nontool = false;
        //MENGECEK TIPE ITEM YANG AKAN DIPINDAHKAN
        if (sourceInv && inv->get(slotSrc)->getBType() == "TOOL") {
            tool = true;
        }
        else if(sourceInv) {
            nontool = true;
        }
        if (sourceCraft && crftab->get(slotSrc)->getBType() == "TOOL") {
            tool = true;
        }
        else if(sourceCraft) {
            nontool = true;
        }

        if (tool && slotCount != 1) {
            ClearBuffer();
            err = "You can't split a tool!\n";
            throw err;
        }

        //INPUT DESTINATION SLOT
        string slotDest;
        int* allSlot = new int[slotCount];
        bool bool_inv = false, craft = false;
        for (int i = 0; i < slotCount;i++) {
            cin >> slotDest;
            if (slotDest[0] == 'C') {
                craft = true;
            }
            else if (slotDest[0] == 'I') {
                bool_inv = true;
            }
            else {
                ClearBuffer();
                err = "You entered an invalid slot!\n";
                throw err;
            }
            if (bool_inv && craft) {
                ClearBuffer();
                err = "You can only move the item to one type of slot!\n";
                throw err;
            }
            slotDest.erase(0, 1);
            allSlot[i] = stoi(slotDest);
            if ((craft && slotSrc >= CRAFT_SIZE) || (bool_inv && slotSrc >= INV_SIZE)) {
                err = "You tried to move an item to invalid slot!\n";
                throw err;
            }
        }

        if (sourceInv && bool_inv && slotCount != 1) {
            err = "You can only move this item to 1 inventory slot\n";
            throw err;
        }

        MoveItemHandler(source,slotCount,allSlot,bool_inv);
    };
    void MoveItemHandler(string sourceSlot,int N, int destSlot[],bool destInv){
        char src = sourceSlot[0];
        sourceSlot.erase(0, 1);
        int slotSrc = stoi(sourceSlot);
        bool sourceInv = isInv(src);
        bool sourceCraft = !sourceInv;
        bool tool = isToolMoved(slotSrc,sourceInv);
        bool craft = !destInv;
        string err = "";

        Item* undef_item = new Item();
        Item* item_inv = NULL;
        Item* item_craft = NULL;
        Item* item_moved = NULL;
        //PROSES PEMINDAHAN BARANG DARI CRAFTING TABLE
        if (sourceCraft) {        //KASUS KETIKA BARANG BERASAL DARI CRAFTING TABLE
            if (tool) {
                item_craft = new Tool(crftab->get(slotSrc)->getID(), crftab->get(slotSrc)->getName(), crftab->get(slotSrc)->getType(), crftab->get(slotSrc)->getBType(), crftab->get(slotSrc)->getDurability());
            }
            else {
                item_craft = new NonTool(crftab->get(slotSrc)->getID(), crftab->get(slotSrc)->getName(), crftab->get(slotSrc)->getType(), crftab->get(slotSrc)->getBType(), crftab->get(slotSrc)->getQuantity());
            }

            if (item_craft->getID() == UNDEFINED_ID) {
                err = "You are trying to move the void...\n";
                throw err;
            }
            else {
                if (craft) {
                    err = "You can't move item from crafting slot to another crafting slot.\n";
                    throw err;
                }
                item_inv = new Item(*inv->get(destSlot[0]));
                bool destKosong = true;
                if (item_inv->getID() != UNDEFINED_ID) {
                    destKosong = false;
                }
                if (!destKosong && item_inv->getID() != item_craft->getID()) {
                    err = "The item you are trying to move to is not of the same type!\n";
                    throw err;
                }

                
                if (destKosong) {
                    inv->set(destSlot[0], item_craft);
                    crftab->set(slotSrc, undef_item);
                }
                else {
                    if (!tool) {
                        item_inv = new NonTool(inv->get(destSlot[0])->getID(), inv->get(destSlot[0])->getName(), inv->get(destSlot[0])->getType(), inv->get(destSlot[0])->getBType(), inv->get(destSlot[0])->getQuantity());
                        if (item_inv->getQuantity() + item_craft->getQuantity() > 64) {
                            err = "The slot is full, you can't move it there!\n";
                            throw err;
                        }
                        item_inv->setQuantity(item_inv->getQuantity() + item_craft->getQuantity());
                        crftab->set(slotSrc, undef_item);
                        inv->set(destSlot[0], item_inv);
                    }
                    else {
                        err = "This slot is occupied by another tool!\n";
                        throw err;
                    }
                    

                }

            }
        }
        if (sourceInv) {      //KASUS KETIKA BARANG BERASAL DARI INVENTORY
            if (tool) {
                item_inv = new Tool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getDurability());
            }
            else {
                item_inv = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
            }
            if (item_inv->getID() == UNDEFINED_ID) {
                err = "You are trying to move the void...\n";
                throw err;
            }
            else {
                if (craft) {
                    if (!tool) {
                        if (N > item_inv->getQuantity()) {
                            err = "You don't have enough item to move\n";
                            throw err;
                        }
                        else {
                            item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                            item_moved->setQuantity(1);
                            
                            for (int i = 0; i < N; i++) {
                                item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                                item_moved->setQuantity(1);
                                item_craft = new NonTool(crftab->get(destSlot[i])->getID(), crftab->get(destSlot[i])->getName(), crftab->get(destSlot[i])->getType(), crftab->get(destSlot[i])->getBType(), crftab->get(destSlot[i])->getQuantity());
                                if (item_craft->getID() != UNDEFINED_ID && item_craft->getID() != item_moved->getID()) {
                                    err = "The item you are trying to move to is not of the same type!\n";
                                    throw err;
                                }
                                else if(item_craft->getID() == UNDEFINED_ID){
                                    crftab->set(destSlot[i], item_moved);
                                }else{
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
                            err = "You can't move an item to an already occupied crafting slot!\n";
                            throw err;
                        }
                        else {
                            Tool* item_moved = new Tool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getDurability());
                            inv->set(slotSrc, undef_item);
                            crftab->set(destSlot[0], item_moved);

                        }
                    
                    }
                    
                }

                if (destInv) {
                    Item* item_inv2 = NULL;
                    item_inv2 = new Item(*inv->get(destSlot[0]));
                    bool destKosong = true;
                    if (item_inv2->getID() != UNDEFINED_ID) {
                        destKosong = false;
                    }
                    if (!destKosong && item_inv2->getID() != item_inv->getID()) {
                        err = "The items are not of the same type.\n";
                        throw err;
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
                            err = "There's a tool already here!\n";
                            throw err;
                        }
                        
                    }
                }
            }
        }
    };
}