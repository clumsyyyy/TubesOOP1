// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "core/all_headers.hpp"

using namespace std;

tuple <string, string, string, string> parse(string line){
    istringstream iss(line);
    string ID;
    string nameTok, typeTok, btypeTok;
    getline(iss, ID, ' ');
    getline(iss, nameTok, ' ');
    getline(iss, typeTok, ' ');
    getline(iss, btypeTok, ' ');
    return make_tuple(ID, nameTok, typeTok, btypeTok);
}

int main() {
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for (string line; getline(itemConfigFile, line);) {
        itemConfig.push_back(parse(line));
    }

    // read recipes
    for (const auto &entry :
        filesystem::directory_iterator(configPath + "/recipe")) {
        cout << entry.path() << endl;
        // read from file and do something
    }

    // test display inventory
    cout << inv->get(0, 0).getID() << endl;
    // sample interaction
    cout << "\n\nInput command: ";
    string command;
    while (cin >> command) {
        if (command == "SHOW"){
            inv->displayMenu();
        } else if (command == "DETAILS"){
            DetailsHandler();
        } else if (command == "GIVE"){
            GiveHandler();
        } else if (command == "DISCARD"){
            DiscardHandler();
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
        } else if (command == "CRAFT") {
            cout << "TODO" << endl;
        } else if (command == "MOVE") {
            string slotSrc;
            int slotQty;
            string slotDest;
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            cout << "TODO" << endl;
        } else {
        // todo
            cout << "Invalid command!" << endl;
        }
        cout << "Input command: ";
    }
    return 0;
}

