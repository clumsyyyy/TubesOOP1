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
		/**
		 * @brief parses recipes for items from a directory
		 * 
		 * @param file 
		 * @return tuple <tuple<int, int>, vector<string>, TupleItem, int> 
		 * a tuple that contains all available recipes
		 */
		tuple <tuple<int, int>, vector<string>, TupleItem, int> parseRecipe(ifstream* file);

		/**
		 * @brief parses items from a file
		 * 
		 * @param line 
		 * @return tuple <string, string, string, string> 
		 * a tuple that contains information regarding an item
		 */
		tuple <string, string, string, string> parseItem(string line);
	public:
		/**
		 * @brief Construct a new Game Manager object
		 * 
		 */
		GameManager();

		/**
		 * @brief Get the Instance object
		 * (refer to the Singleton design pattern)
		 * @return GameManager
		 */
		static GameManager getInstance();

		/*VARIABLES*/
		vector <TupleItem> itemConfig;
		vector <TupleRecipe> recipeConfig;
		Inventory inv;
		CraftingTable crftab;
	};
}


#endif