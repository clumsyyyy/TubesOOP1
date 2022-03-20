#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "vars.hpp"
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <filesystem>
#include "crafting_table.hpp"
#include "inventory.hpp"
using namespace std;

namespace Lib {
	class GameManager {
	private:
		tuple <tuple<int, int>, vector<string>, TupleItem, int> parseRecipe(ifstream* file);
		tuple <string, string, string, string> parseItem(string line);
	public:
		GameManager();
		vector <TupleItem> itemConfig;
		vector <TupleRecipe> recipeConfig;
		Inventory inv;
		CraftingTable crftab;
		void Load();
	};
}


#endif