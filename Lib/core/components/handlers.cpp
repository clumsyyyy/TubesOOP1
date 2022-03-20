#include "headers/handlers.hpp"
#include "headers/exception.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"
#include <limits>
#include <fstream>
#include <iostream>

namespace Lib {
    void DetailsHandler(string mode, int i) {
        if (mode == "ALL") {
            cout << &(gm.inv);
            cout << &(gm.crftab);
        }
        else if (mode == "ITEM") {
            gm.inv.specify(i);
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
        for (tuple tup : gm.itemConfig) {
            if (get<1>(tup) == name) {
                if (get<3>(tup) == "NONTOOL") {
                    NonTool* NT = new NonTool(tup, temp);
                    gm.inv.addNonTool(NT, 0);
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
                    Tool* T = new Tool(tup, durability);
                    gm.inv.addTool(T, temp);
                }
                return;
            }
        }
        throw new AddException(name);
    }

    void DiscardHandler(string slot, int quant) {
        int index = stoi(slot.substr(1, slot.length() - 1));
        if (gm.inv[index]->isNonTool()) {
            gm.inv.discard(quant, index);
        }
        else {
            gm.inv.set(index, new Item());
        }
    }

    void UseHandler(string slot) {
        try {
            int index = stoi(slot.substr(1, slot.length() - 1));
            Item* it = gm.inv[index];
            if (it->isNonTool()) {
                throw new UseException(it->getName());
            }
            else {
                if (it->getDurability() == 1) {
                    it->useItem();
                    gm.inv.set(index, new Item());
                }
                else {
                    it->useItem();
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
        if (sourceInv && gm.inv[slotSrc]->isTool())
            tool = true;
        else if(sourceInv)
            nontool = true;

        if (sourceCraft && gm.crftab[slotSrc]->isTool())
            tool = true;
        else if(sourceCraft)
            nontool = true;

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
        return;
    }
}