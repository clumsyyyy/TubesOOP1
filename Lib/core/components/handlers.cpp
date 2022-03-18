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
        bool sourceInv = (src == 'I');
        bool sourceCraft = !sourceInv;
        bool craft = !destInv;
        //PROSES PEMINDAHAN BARANG DARI CRAFTING TABLE
        if (sourceCraft) {        //KASUS KETIKA BARANG BERASAL DARI CRAFTING TABLE
            if (craft) {
                MoveException *err = new MoveException("CRAFTTOCRAFT");
                throw *err;
            }else{
                try{
                    crftab->toInv(slotSrc,destSlot);
                }catch (MoveException err){
                    throw err;
                }
            }
        }
        if (sourceInv) {      //KASUS KETIKA BARANG BERASAL DARI INVENTORY
            if (craft) {
                try{
                    inv->toCraft(slotSrc,destSlot,N);
                }catch(MoveException err){
                    throw err;
                }
            }
            if (destInv) {
                try{
                    inv->toAnotherSlot(slotSrc,destSlot);
                }catch(MoveException err){
                    throw err;
                }
            }
        }
    };
}