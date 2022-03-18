#include "headers/handlers.hpp"
#include "headers/exception.hpp"
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
        try {
            GiveChecker(name, temp);
        }
        catch (BaseException* e) {
            e->printMessage();
        }

    }

    void GiveChecker(string name, int temp) {
        bool found = false;
        for (tuple tup : *itemConfig) {
            if (get<1>(tup) == name) {
                found = true;
                if (get<3>(tup) == "NONTOOL") {
                    NonTool* NT = new NonTool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                    inv->addNonTool(NT, 0);
                    break;
                }
                else {
                    Tool* T = new Tool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), 10);
                    inv->addTool(T, temp);
                    break;
                }
            }
        }
        if (!found) {
            throw new AddException(name);
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

    void UseHandler() {
        try {
            string slot;
            cin >> slot;
            int index = stoi(slot.substr(1, slot.length() - 1));
            if (inv->get(index)->getBType() == "NONTOOL") {
                throw new UseException(inv->get(index)->getName());
            }
            else {
                if (inv->get(index)->getDurability() == 1) {
                    inv->get(index)->useItem();
                    inv->set(index, new Item());
                }
                else {
                    inv->get(index)->useItem();
                }

            }
        }
        catch (BaseException* e) {
            e->printMessage();
        }
    }

    void CraftingHandler() {
        try {
            Crafting::crafting_proses();
        }
        catch (BaseException* e) {
            e->printMessage();
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

        if (slotCount < 1) {
            MoveException *err =new MoveException("INVALIDSLOT");
            throw *err;
        }

        char src = source[0];
        string source1 = source;
        source1.erase(0, 1);
        int slotSrc = stoi(source1);
        if (src != 'C' && src != 'I') {           //CHECKING SOURCE SLOT APAKAH VALID ATO TIDAK
            ClearBuffer();
            MoveException *err = new MoveException("INVALID");
            throw *err;
        }

        if ((src == 'C' && slotSrc >= CRAFT_SIZE) || (src == 'I' && slotSrc >= INV_SIZE)) {
            ClearBuffer();
            MoveException *err = new MoveException("INVALID");
            throw *err;
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
            MoveException *err = new MoveException("INVALIDSLOT");
            throw *err;
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
                MoveException *err = new MoveException("INVALIDDEST"); 
                throw *err;
            }
            if (bool_inv && craft) {
                ClearBuffer();
                MoveException *err = new MoveException("DOUBLETYPEDEST");
                throw *err;
            }
            slotDest.erase(0, 1);
            allSlot[i] = stoi(slotDest);
            if ((craft && slotSrc >= CRAFT_SIZE) || (bool_inv && slotSrc >= INV_SIZE)) {
                MoveException *err = new MoveException("INVALIDDEST");
                throw *err;
            }
        }

        if (sourceInv && bool_inv && slotCount != 1) {
            string a = "MOVETO2INV";
            MoveException *err = new MoveException(a);
            throw *err;
        }
        try {
            MoveItemHandler(source, slotCount, allSlot, bool_inv);
        }catch(MoveException err) {
            throw err;
        }
        
    };
    void MoveItemHandler(string sourceSlot,int N, int destSlot[],bool destInv){
        char src = sourceSlot[0];
        sourceSlot.erase(0, 1);
        int slotSrc = stoi(sourceSlot);
        bool sourceInv = isInv(src);
        bool sourceCraft = !sourceInv;
        bool tool = isToolMoved(slotSrc, sourceInv);
        bool craft = !destInv;

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
                MoveException *err = new MoveException("VOID");
                throw *err;
            }
            else {
                if (craft) {
                    MoveException *err = new MoveException("CRAFTTOCRAFT");
                    throw *err;
                }
                item_inv = new Item(*inv->get(destSlot[0]));
                bool destKosong = true;
                if (item_inv->getID() != UNDEFINED_ID) {
                    destKosong = false;
                }
                if (!destKosong && item_inv->getID() != item_craft->getID()) {
                    MoveException *err = new MoveException("DIFFTYPE");
                    throw *err;
                }


                if (destKosong) {
                    inv->set(destSlot[0], item_craft);
                    crftab->set(slotSrc, undef_item);
                }
                else {
                    if (!tool) {
                        item_inv = new NonTool(inv->get(destSlot[0])->getID(), inv->get(destSlot[0])->getName(), inv->get(destSlot[0])->getType(), inv->get(destSlot[0])->getBType(), inv->get(destSlot[0])->getQuantity());
                        if (item_inv->getQuantity() + item_craft->getQuantity() > 64) {
                            MoveException *err = new MoveException("FULL");
                            throw *err;
                        }
                        item_inv->setQuantity(item_inv->getQuantity() + item_craft->getQuantity());
                        crftab->set(slotSrc, undef_item);
                        inv->set(destSlot[0], item_inv);
                    }
                    else {
                        MoveException *err = new MoveException("TOOL");
                        throw *err;
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
                MoveException *err = new MoveException("VOID");
                throw *err;
            }
            else {
                if (craft) {
                    if (!tool) {
                        if (N > item_inv->getQuantity()) {
                            MoveException *err = new MoveException("NOTENOUGH");
                            throw *err;
                        }
                        else {
                            item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                            item_moved->setQuantity(1);

                            for (int i = 0; i < N; i++) {
                                item_moved = new NonTool(inv->get(slotSrc)->getID(), inv->get(slotSrc)->getName(), inv->get(slotSrc)->getType(), inv->get(slotSrc)->getBType(), inv->get(slotSrc)->getQuantity());
                                item_moved->setQuantity(1);
                                item_craft = new NonTool(crftab->get(destSlot[i])->getID(), crftab->get(destSlot[i])->getName(), crftab->get(destSlot[i])->getType(), crftab->get(destSlot[i])->getBType(), crftab->get(destSlot[i])->getQuantity());
                                if (item_craft->getID() != UNDEFINED_ID && item_craft->getID() != item_moved->getID()) {
                                    MoveException *err = new MoveException("DIFFTYPE");
                                    throw *err;
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
                            MoveException *err = new MoveException("TOOL");
                            throw *err;
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
                        MoveException *err = new MoveException("DIFFTYPE");
                        throw *err;
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
                            MoveException *err = new MoveException("TOOL");
                            throw *err;
                        }

                    }
                }
            }
        }
    };
}