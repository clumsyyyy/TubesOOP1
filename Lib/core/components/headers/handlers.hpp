#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "item.hpp"
#include "table.hpp"
#include <string>

namespace Lib {
	void DetailsHandler(string, int);
	void GiveHandler(string, int);
	void DiscardHandler( int, int);
	void UseHandler(string);
	void CraftingHandler();
	void GiveChecker(string name, int temp);
	void MoveHandler(string source, int slotCount, vector<string>);
	void MoveItemHandler(string sourceSlot,int N, int destSlot[], bool destInv);
	void ExportHandler(string outputPath);
	void ClearBuffer();
	void ExportHandler(string path);
}

#endif