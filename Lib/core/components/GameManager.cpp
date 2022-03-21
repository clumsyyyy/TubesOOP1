#include "headers/GameManager.hpp"
#include <filesystem>
#include <sstream>

namespace Lib {
    GameManager::GameManager() {
        string configPath = "../config";
        string itemConfigPath = configPath + "/item.txt";

        // read item from config file
        ifstream itemConfigFile(itemConfigPath);
        for (string line; getline(itemConfigFile, line);) {
            itemConfig.push_back(parseItem(line));
        }
        // read recipes
        for (const auto& entry :
            filesystem::directory_iterator(configPath + "/recipe")) {
            ifstream* recipeConfigFile = new ifstream(entry.path());
            recipeConfig.push_back(parseRecipe(recipeConfigFile));
            delete recipeConfigFile;
            // read from file and do something
        }
    };
    GameManager GameManager::getInstance() {
        static GameManager gm;
        return gm;
    }
    tuple <string, string, string, string> GameManager::parseItem(string line) {
        istringstream iss(line);
        string ID;
        string nameTok, typeTok, btypeTok;
        getline(iss, ID, ' ');
        getline(iss, nameTok, ' ');
        getline(iss, typeTok, ' ');
        getline(iss, btypeTok, ' ');
        return make_tuple(ID, nameTok, typeTok, btypeTok);
    }
    tuple <tuple<int, int>, vector<string>, TupleItem, int> GameManager::parseRecipe(ifstream* file) {
        int i = 0, n = 0, m = 0;
        vector<string> recipeList;
        string ID, name, type, btype;
        int quantity;
        for (string line; getline(*file, line);) {
            if (i == 0) {
                istringstream iss(line);
                string row, col;
                getline(iss, row, ' ');
                getline(iss, col, ' ');
                n = stoi(row);
                m = stoi(col);
            }
            else if (i <= n) {
                istringstream iss(line);
                for (int j = 0; j < m; j++) {
                    string temp;
                    getline(iss, temp, ' ');
                    if (temp == "-") {
                        recipeList.push_back("UNDEFINED");
                    }
                    else {
                        recipeList.push_back(temp);
                    }

                }
            }
            else {
                istringstream iss(line);
                string tempname, tempquantity;
                getline(iss, tempname, ' ');
                getline(iss, tempquantity, ' ');
                name = tempname;
                quantity = stoi(tempquantity);
            }
            i++;
        }
        for (tuple tup : itemConfig) {
            if (get<1>(tup) == name) {
                ID = get<0>(tup);
                type = get<2>(tup);
                btype = get<3>(tup);
                break;
            }
        }
        return make_tuple(make_tuple(n, m), recipeList, make_tuple(ID, name, type, btype), quantity);
    }
}
