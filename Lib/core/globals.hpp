#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "components/headers/item.hpp"
#include "components/headers/inventory.hpp"
#include "components/headers/crafting_table.hpp"
#include "components/headers/crafting.hpp"
#include "components/headers/vars.hpp"
#include <vector>

namespace Lib {
	extern Inventory* inv;
	extern CraftingTable* crftab;
	extern vector <TupleItem>* itemConfig;
	extern vector <TupleRecipe>* recipeConfig;
}
#endif