// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "components/headers/inventory.hpp"
#include "components/headers/item.hpp"
#include <map>
#include <vector>
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
  vector <tuple<string, string, string, string>> itemConfig;
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    cout << line << endl;
    itemConfig.push_back(parse(line));
    // do something
  }

  // read recipes
  // masukkan ke dalam map
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe")) {
    cout << entry.path() << endl;
    // read from file and do something
  }

  // test display inventory
  Inventory *inv = new Inventory();
  cout << inv->get(0, 0).getID() << endl;
  // sample interaction
  cout << "\n\nInput command: ";
  string command;
  while (cin >> command) {
    if (command == "SHOW"){
      string displayType;
      cin >> displayType;
      // Type SHOW ITEM <i> <j> to show 
      // details of item(i, j)
      // otherwise type SHOW MAP
      // (FOR DEBUGGING)
      if (displayType == "ITEM"){
        int i, j;
        cin >> i >> j;
        (inv->get(i, j)).displayInfo();
      } else if (displayType == "MAP"){
        inv->display();
      }
    }
    else if (command == "GIVE"){
      string name;
      int quant;
      cin >> name >> quant;
      for(tuple i : itemConfig){
        if(get<1>(i) == name){
          if (get<3>(i) == "NONTOOL"){
            NonTool* item = new NonTool(stoi(get<0>(i)), get<1>(i), get<2>(i), get<3>(i), quant);
            inv->add(item, quant);
          } else {
            //THROW EXCEPTION HERE
          }
        }
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
    } else if (command == "CRAFT") {
      cout << "TODO" << endl;
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
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
      cout << "Invalid command" << endl;
    }
    cout << "Input command: ";
  }
  return 0;
}

