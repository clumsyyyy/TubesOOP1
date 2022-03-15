#include "globals.hpp"

Inventory* inv = new Inventory();
CraftingTable* crftab = new CraftingTable();
vector <tuple<string, string, string, string>> *itemConfig = new vector <tuple<string, string, string, string>>();
vector <tuple<tuple<int,int>,vector<string>,tuple<int,string>>> *recipeConfig = new vector <tuple<tuple<int, int>, vector<string>, tuple<int, string>>>();