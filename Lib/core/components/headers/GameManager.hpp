#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "vars.hpp"
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

namespace Lib {
	class GameManager {
	private:
		GameManager();
	public:
		static vector <TupleItem> itemConfig;
		static vector <TupleRecipe> recipeConfig;
		static GameManager& getInstance();
		tuple <tuple<int, int>, vector<string>, TupleItem, int> parseRecipe(ifstream* file);
		tuple <string, string, string, string> parseItem(string line);
		void Load();
	};
}


#endif