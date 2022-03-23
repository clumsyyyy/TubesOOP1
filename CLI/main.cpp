#include <string>
#include <vector>
#include "core/all_headers.hpp"

using namespace Lib;

int main() {
    cout << "Input command: ";
    string command;
    while (cin >> command) {
        if (command == "SHOW")
        {
            cout << gm.crftab; // Display Crafting Table
            cout << gm.inv;    // Display Inventory
        } 
        else if (command == "DETAILS")
        {
            // USAGE: DETAILS ALL
            // USAGE: DETAILS ITEM <SLOT_ID>
            string mode;
            cin >> mode;
            if (mode == "ALL") {
                DetailsHandler(mode, NULL);
            }
            else if (mode == "ITEM") {
                int i;
                cin >> i;
                DetailsHandler(mode, i);
            }
        } 
        else if (command == "GIVE")
        {
            // USAGE: GIVE <ITEM_NAME> <ITEM_QTY>
            string name;
            int qty;
            cin >> name >> qty;
            GiveHandler(name, qty);
        }
        else if (command == "DISCARD") 
        {
            // USAGE: DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>
            string slot;
            cin >> slot;
            int index = stoi(slot.substr(1, slot.length() - 1)); // Getting the index of the slot
            int qty = 1;
            if (gm.inv[index]->isNonTool()) {
                cin >> qty;
            }
            DiscardHandler(index, qty);
      
        }
        else if (command == "USE") 
        {
            // USAGE: USE <INVENTORY_SLOT_ID> 
            // For Tool item only
            string slot;
            cin >> slot;
            UseHandler(slot);
        } 
        else if (command == "CRAFT") 
        {
            // USAGE: CRAFT 
            // Can be used if the crafting table is valid
            CraftingHandler();
        } 
        else if (command == "MOVE") 
        {   
            // 1. Moving item from inventory to crafting table 
            // Item with quantity > 1 can be moved to several slots
            // USAGE: MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> <CRAFTING_SLOT_ID_2> ...
            // 2. Stacking item (for NonTool item)
            // USAGE: MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>
            // 3. Returning item from crafting table to inventory
            // USAGE: MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>
            string slotSrc;
            int slotQty;
            
            cin >> slotSrc >> slotQty;
            vector<string> slotDestV;
            for (int i = 0; i < slotQty; i++) {
                string slotDest;
                cin >> slotDest;
                slotDestV.push_back(slotDest);
            }
            try{
                MoveHandler(slotSrc,slotQty, slotDestV);
            }catch(MoveException * err){
                err->printMessage();
            }
                
            
        }
        else if (command == "EXPORT") 
        {
            // USAGE: EXPORT <FILE_NAME>
            string outputPath;
            cin >> outputPath;
            ExportHandler(outputPath);
            cout << "Exported" << endl;
        }
        else 
        {
            cout << "Invalid command!" << endl;
        }
        cout << "Input command: ";
        ClearBuffer();
    }
    return 0;
}

