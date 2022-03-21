#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "vars.hpp"
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <filesystem>
#include "table.hpp"
using namespace std;

namespace Lib {
	class GameManager {
	private:
		tuple <tuple<int, int>, vector<string>, TupleItem, int> parseRecipe(ifstream* file);
		tuple <string, string, string, string> parseItem(string line);
	public:
		GameManager();
		static GameManager getInstance();
		vector <TupleItem> itemConfig;
		vector <TupleRecipe> recipeConfig;
		Inventory inv;
		CraftingTable crftab;
	};
}


#endif