#include "headers/handlers.hpp"
#include "headers/exception.hpp"
#include "../globals.hpp"
#include <limits>
#include <fstream>
#include <iostream>

namespace Lib {
    void DetailsHandler(string mode, int i) {
        if (mode == "ALL") {
             //inv->displayDetails();
             //crftab->displayDetails();
            cout << *inv;
            cout << *crftab;
        }
        else if (mode == "ITEM") {
            inv->specify(i);
            cout << endl;
        }
    }

    void GiveHandler(string name, int temp) {
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
                    int durability;
                    string kind;
                    istringstream iss(get<1>(tup));
                    getline(iss,kind,'_');
                    if (kind == "WOODEN") {
                        durability = 4;
                    } else if (kind == "STONE") {
                        durability = 6;
                    } else if (kind == "IRON") {
                        durability = 8;
                    } else if (kind == "DIAMOND") {
                        durability = 10;
                    } else {
                        durability = 0;
                    }
                    Tool* T = new Tool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), durability);
                    inv->addTool(T, temp);
                    break;
                }
            }
        }
        if (!found) {
            throw new AddException(name);
        }
    }

    void DiscardHandler(string slot, int quant) {
        int index = stoi(slot.substr(1, slot.length() - 1));
        if (inv->get(index)->isNonTool()) {
            inv->discard(quant, index);
        }
        else {
            inv->set(index, new Item());
        }
    }

    void UseHandler(string slot) {
        try {
            int index = stoi(slot.substr(1, slot.length() - 1));
            if (inv->get(index)->isNonTool()) {
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


    void MoveHandler(string source, int slotCount, vector<string> slotDestV) {
        if (slotCount < 1) {
            throw new MoveException("INVALIDSLOT");
        }
        char src = source[0];
        string source1 = source;
        source1.erase(0, 1);
        int slotSrc = stoi(source1);
        if (src != 'C' && src != 'I') {           //CHECKING SOURCE SLOT APAKAH VALID ATO TIDAK
            ClearBuffer();
            throw new MoveException("INVALID");
        }

        if ((src == 'C' && slotSrc >= CRAFT_SIZE) || (src == 'I' && slotSrc >= INV_SIZE)) {
            ClearBuffer();
            throw new MoveException("INVALID");
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
        if (sourceInv && inv->get(slotSrc)->isTool()) {
            tool = true;
        }
        else if(sourceInv) {
            nontool = true;
        }
        if (sourceCraft && crftab->get(slotSrc)->isTool()) {
            tool = true;
        }
        else if(sourceCraft) {
            nontool = true;
        }

        if (tool && slotCount != 1) {
            ClearBuffer();
            throw new MoveException("INVALIDSLOT");
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
                ClearBuffer();
                throw new MoveException("INVALIDDEST");
            }
            if (bool_inv && craft) {
                ClearBuffer();
                throw new MoveException("DOUBLETYPEDEST");
            }
            slotDest.erase(0, 1);
            allSlot[i] = stoi(slotDest);
            if ((craft && slotSrc >= CRAFT_SIZE) || (bool_inv && slotSrc >= INV_SIZE)) {
                throw new MoveException("INVALIDDEST");
            }
        }

        if (sourceInv && bool_inv && slotCount != 1) {
            throw new MoveException("MOVETO2INV");
        }
        try {
            MoveItemHandler(source, slotCount, allSlot, bool_inv);
        } catch(MoveException* err) {
            err->printMessage();
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
                throw new MoveException("CRAFTTOCRAFT");
            }else{
                crftab->toInv(slotSrc,destSlot);
            }
        }
        if (sourceInv) {      //KASUS KETIKA BARANG BERASAL DARI INVENTORY
            if (craft) {
                try{
                    inv->toCraft(slotSrc,destSlot,N);
                }catch(MoveException* err){
                    err->printMessage();
                }
            }
            if (destInv) {
                try{
                    inv->toAnotherSlot(slotSrc,destSlot);
                }catch(MoveException* err){
                    err->printMessage();
                }
            }
        }
        
    }
    //void ExportHandler(string outputPath)
    //{
    //    // todo : tentukan path untuk tests
    //    ofstream outputFile;
    //    outputFile.open(outputPath);
    //    for (int i = 0; i < 27; i++) {
    //        outputFile
    //    	<< (inv->get(i)->getID() == -999 ? 
    //            0 : inv->get(i)->getID())
    //    	<< ":"
    //    	<< (inv->get(i)->getType() == "TOOL" ? // todo : perbaiki bug untuk getDurability
    //    		inv->get(i)->getDurability() : inv->get(i)->getQuantity()) << endl;
    //    }
    //    outputFile.close();
    //};

    void ExportHandler(string path) {
        ofstream outputFile(path);
        for (int i = 0; i < 27; i++) {
            string type = inv->get(i)->getBType();
            if (type == "NONTOOL") {
                outputFile << inv->get(i)->getID() << ":" << inv->get(i)->getQuantity() << endl;
            }
            else if (type == "TOOL") {
                outputFile << inv->get(i)->getID() << ":" << inv->get(i)->getDurability() << endl;
            }
            else if (type == "UNDEFINED") {
                outputFile << "0:0" << endl;
            }
        }
        cout << "Exported" << endl;
        outputFile.close();
        return;
    }
}