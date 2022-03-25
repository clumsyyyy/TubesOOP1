#include <string>
#include <vector>
#include "../Lib/core/all_headers.hpp"

using namespace Lib;

void title() {
    cout << "" << endl;
    cout << " ___ ___    ___  ____   ____  ____    ____  ____  ____  ____  " << endl;
    cout << "|   |   |  /  _]|    | /    ||    \\  /    ||    ||    ||    \\ " << endl;
    cout << "| _   _ | /  [_ |__  ||  o  ||  D  )|  o  ||__  | |  | |  _  |" << endl;
    cout << "|  \\_/  ||    _]__|  ||     ||    / |     |__|  | |  | |  |  |" << endl;
    cout << "|   |   ||   [_/  |  ||  _  ||    \\ |  _  /  |  | |  | |  |  |" << endl;
    cout << "|   |   ||     \\  `  ||  |  ||  .  \\|  |  \\  `  | |  | |  |  |" << endl;
    cout << "|___|___||_____|\\____||__|__||__|\\_||__|__|\\____||____||__|__|" << endl;
    cout << "[ A MineCraft crafting table simulator ]" << endl;
    cout << "[ Use command `HELP` to display available commands! ]" << endl;
}

int main() {
    title();
    cout << "\n[INPUT COMMAND] | >> ";
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
                DetailsHandler(mode, -1);
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
            int index = -1;
            int qty = 1;
            try {
                index = stoi(slot.substr(1, slot.length() - 1));
                if (gm.inv[index] != nullptr && gm.inv[index]->isNonTool()) {
                    cin >> qty;
                }
            }
            catch (...) {
                index = -1;
                qty = 1;
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
            cout << "Exported file to path " << outputPath << "!" << endl;
        }
        else if (command == "EXIT"){
            cout << "Exiting program..." << endl;
            return 0;
        }
        else if (command == "HELP") {
            // USAGE: HELP
            cout << "=================================== HELP MENU ==================================\n" << endl;
            cout << "| >> SHOW" << endl;
            cout << "To display both the crafting table and the inventory." << endl;
            cout << "Inventory: [(<SLOT_ID>) <ITEM_ID> <QUANTITY/DURABILITY>)]" << endl;
            cout << "Crafting table: [(<SLOT_ID>) <ITEM_ID> <QUANTITY/DURABILITY)]\n" << endl;

            cout << "| >> DETAILS ALL" << endl;
            cout << "To display details of items in the crafting table and the inventory.\n" << endl;

            cout << "| >> DETAILS ITEM <SLOT_ID>" << endl;
            cout << "To display details of a specific item in a slot.\n" << endl;

            cout << "| >> GIVE <ITEM_NAME> <ITEM_QTY>" << endl;
            cout << "Adds item to the inventory as much as quantity.\n" << endl;

            cout << "| >> DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>" << endl;
            cout << "Discards item from an inventory slot as much as quantity." << endl;
            cout << "[IMPORTANT] For discarding a tool item, use `DISCARD <INVENTORY_SLOT_ID>\n" << endl;

            cout << "| >> USE <INVENTORY_SLOT_ID>" << endl;
            cout << "Uses a tool item from an inventory slot. Cannot be used with a non-tool item.\n" << endl;

            cout << "| >> MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> <CRAFTING_SLOT_ID_2> ..." << endl;
            cout << "Moves N amount of items from the inventory to crafting slots." << endl;
            cout << "[IMPORTANT] Enter as much crafting slots as the N items!\n" << endl;

            cout << "| >> MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>" << endl;
            cout << "Moves all items from one inventory slot to another slot.\n" << endl;

            cout << "| >> MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>" << endl;
            cout << "Moves all items from one crafting slot to one inventory slot.\n" << endl;

            cout << "| >> EXPORT <DIRECTORY>" << endl;
            cout << "Exports inventory into a file." << endl;
            cout << "[IMPORTANT] Exported file will be saved with the relative path to this program." << endl;
            cout << "Enter the desired path and save with a .out filetype (e.g. export/test.out)\n" << endl;

            cout << "| >> HELP" << endl;
            cout << "Displays this menu.\n" << endl;

            cout << "| >> EXIT" << endl;
            cout << "Exits this CLI program.\n" << endl;
            
            cout << "================================================================================\n" << endl;
        }
        else 
        {
            cout << "Invalid command! Type `HELP` to see available commands." << endl;
        }
        cout << "\n[INPUT COMMAND] | >> ";
        cin.clear();
        ClearBuffer();
    }
    // return 0;
}

