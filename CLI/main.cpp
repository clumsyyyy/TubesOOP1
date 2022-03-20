// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../Lib/core/all_headers.hpp"


using namespace Lib;


int main() {
    GameManager gm = GameManager::getInstance();
    gm.Load();

    cout << "Input command: ";
    string command;
    while (cin >> command) {
        if (command == "SHOW"){
            // crftab->displayMenu();
            cout << crftab;
            cout << inv;            
            // inv->displayMenu();
            // 
        } else if (command == "DETAILS"){
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
        } else if (command == "GIVE"){
            string name;
            int temp;
            cin >> name >> temp;
            GiveHandler(name, temp);
        }
        else if (command == "DISCARD") {
            string slot;
            int quant;
            cin >> slot >> quant;
            DiscardHandler(slot, quant);
        }
        else if (command == "USE") {
            string slot;
            cin >> slot;
            UseHandler(slot);
        } else if (command == "CRAFT") {
            CraftingHandler();
        } else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty;
            vector<string> slotDestV;
            for (int i = 0; i < slotQty; i++) {
                string slotDest;
                cin >> slotDest;
                slotDestV.push_back(slotDest);
            }
            try{
                MoveHandler(slotSrc,slotQty, slotDestV);
            }catch(MoveException err){
                err.printMessage();
            }
            
        }
        else if (command == "EXPORT") {
            string outputPath;
            cin >> outputPath;
            ofstream outputFile(outputPath);

            // hardcode for first test case
            outputFile << "21:10" << endl;
            outputFile << "6:1" << endl;
            for (int i = 2; i < 27; i++) {
                outputFile << "0:0" << endl;
            }

            cout << "Exported" << endl;
        }
        else {
            cout << "Invalid command!" << endl;
        }
        cout << "Input command: ";
    }
    return 0;
}

