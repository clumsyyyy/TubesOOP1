#include "headers/handlers.hpp"
#include "../globals.hpp"
#include <limits>

void DetailsHandler(){
    string mode;
    cin >> mode;
    if (mode == "ALL"){
        inv->displayDetails();
    } else if (mode == "ITEM"){
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
    for(tuple tup : *itemConfig) {
        if(get<1>(tup) == name) {
            if (get<3>(tup) == "NONTOOL"){
                NonTool* NT = new NonTool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                inv->addNonTool(NT);
                break;
            } else {
                Tool* T = new Tool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                inv->addTool(T);
                break;
            }
        } else {
            //throw exception here
        }
    }
}

void DiscardHandler(){
    string slot;
    int quant;
    cin >> slot >> quant;
    int index = stoi(slot.substr(1, slot.length() - 1));
    if (inv->get(index)->getBType() == "NONTOOL"){
        inv->discard(quant, index);
    } else {
        inv->set(index, new Item());
    }
}

void CraftingHandler() {
    for (tuple tup: *recipeConfig) {
        int sum = 0;
        int min = 0;        
        string name;
        Crafting crf(tup);
        crf.recipe();
        name = crf.getName();
        sum = crf.getSum();
        if (sum > 0){
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
                crftab->get(i)->setQuantity(crftab->get(i)->getQuantity()-1);
            }
        
        }
        GiveChecker(name, durability);
        crf.returning();
    } else {
        throw "Recipe not found\n";    
    }
}

void ClearBuffer(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
};

void MoveHandler(string source, int slotCount){
    string err = "";

    if(slotCount<1){
        err = "Invalid slot count\n";
        throw err;
    }

    char src = source[0];
    source.erase(0,1);
    int slotSrc = stoi(source);
    if(src != 'C' && src != 'I'){           //CHECKING SOURCE SLOT APAKAH VALID ATO TIDAK
        ClearBuffer();
        err = "You move an invalid slot!\n";
        throw err;
    }

    if((src == 'C' && slotSrc >= CRAFT_SIZE) || (src == 'I' && slotSrc >= INV_SIZE)){
        ClearBuffer();
        err = "You move an invalid slot!\n";
        throw err;
    }
    
    bool sourceCraft = false, sourceInv = false;
    if(src == 'C'){
        sourceCraft = true;
    }else{
        sourceInv = true;
    };

    //INPUT DESTINATION SLOT
    string slotDest;
    int *allSlot = new int[slotCount];
    bool bool_inv = false, craft = false;
    for(int i = 0; i<slotCount;i++){
        cin >> slotDest;
        if(slotDest[0] == 'C'){
            craft = true;
        }else if(slotDest[0] == 'I'){
            bool_inv = true;
        }else{
            ClearBuffer();
            err = "You entered an invalid slot!\n";
            throw err;
        }
        if(bool_inv && craft){
            ClearBuffer();
            err = "You can only move the item to one type of slot!\n";
            throw err;
        }
        slotDest.erase(0,1);
        allSlot[i] = stoi(slotDest);
        if((craft && slotSrc >= CRAFT_SIZE) || (bool_inv && slotSrc >= INV_SIZE)){
            err = "You tried to move an item to invalid slot!\n";
            throw err;
        }
    }

    if(sourceInv && bool_inv && slotCount != 1){
        err = "You can only move this item to 1 inventory slot\n";
        throw err;
    }

    //PROSES PEMINDAHAN BARANG DARI CRAFTING TABLE
    if(sourceCraft){        //KASUS KETIKA BARANG BERASAL DARI CRAFTING TABLE
        Item *item_craft = new Item(*crftab->get(slotSrc));
        if(item_craft->getID() == UNDEFINED_ID){
            err = "You are trying to move the void...\n";
            throw err;
        }else{
            if(craft){
                err = "You can't move item from crafting slot to another crafting slot.\n";
                throw err;
            }
            Item *item_inv = new Item(*inv->get(allSlot[0]));
            bool destKosong = true;
            if(item_inv->getID() != UNDEFINED_ID){
                destKosong = false;
            }
            if(!destKosong && item_inv->getID() != item_craft->getID()){
                err = "The item you are trying to move to is not of the same type.\n";
                throw err;
            }

            Item *undef_item = new Item();
            if(destKosong){
                item_craft->setQuantity(1);
                inv->set(allSlot[0],item_craft);
                crftab->set(slotSrc,undef_item);
            }else{
                item_inv->setQuantity(item_inv->getQuantity()+1);
                crftab->set(slotSrc,undef_item);
                inv->set(allSlot[0],item_inv);
            
            }

        }
    }
    if(sourceInv){      //KASUS KETIKA BARANG BERASAL DARI INVENTORY
        Item * item_inv = new Item(*inv->get(slotSrc));
        if(item_inv->getID() == UNDEFINED_ID){
            err = "You are trying to move the void...\n";
            throw err;
        }else{
            if(craft){
                if(slotCount>item_inv->getQuantity()){
                    err = "You don't have enough item to move\n";
                    throw err;
                }else{
                    for(int i = 0; i<slotCount; i++){
                        Item *item_craft = new Item(*crftab->get(allSlot[i]));
                        if(item_craft->getID() != UNDEFINED_ID){
                            err ="You can't move an item to an already occupied crafting slot!\n";
                            throw err;
                        }else{
                            Item *item_moved = new Item(*inv->get(slotSrc));
                            item_moved->setQuantity(1);
                            crftab->set(allSlot[i],item_moved);
                        }
                    }
                    item_inv->setQuantity(item_inv->getQuantity() - slotCount);
                    inv->set(slotSrc,item_inv);
                }
            }

            if(bool_inv){
                Item *item_inv2 = new Item(*inv->get(allSlot[0]));
                bool destKosong = true;
                Item *undef_item = new Item();
                if(item_inv2->getID() != UNDEFINED_ID){
                    destKosong = false;
                }
                if(!destKosong && item_inv2->getID() != item_inv->getID()){
                    err = "The items are not of the same type.\n";
                    throw err;
                }
                if(destKosong){
                    inv->set(allSlot[0],item_inv);
                    inv->set(slotSrc,undef_item);
                }else{
                    int kurang = 64-item_inv2->getQuantity();
                    if(item_inv->getQuantity()>kurang){
                        item_inv2->setQuantity(64);
                        item_inv->setQuantity(item_inv->getQuantity()-kurang);
                        inv->set(slotSrc,item_inv);
                        inv->set(allSlot[0],item_inv2);
                    }else{
                        item_inv2->setQuantity(item_inv2->getQuantity() + item_inv->getQuantity());
                        Item * undef_item = new Item();
                        inv->set(slotSrc,undef_item);
                        inv->set(allSlot[0],item_inv2);
                    }
                }
            }
        }
    }
};