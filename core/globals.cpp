#include "globals.hpp"

Inventory* inv = new Inventory();
CraftingTable* crftab = new CraftingTable();
vector <tuple<string, string, string, string>> itemConfig;
vector <tuple<int,vector<string>,tuple<int,string>>> recipeConfig;