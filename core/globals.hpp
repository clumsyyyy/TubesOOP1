#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "components/headers/item.hpp"
#include "components/headers/inventory.hpp"
#include "components/headers/crafting_table.hpp"
#include <vector>
#include <string>

extern Inventory* inv;
extern CraftingTable* crftab;
extern vector <tuple<string, string, string, string>> itemConfig;
extern vector <tuple<int,vector<string>,tuple<int,string>>> recipeConfig;
#endif