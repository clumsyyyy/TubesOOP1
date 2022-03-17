#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "item.hpp"
#include "inventory.hpp"
#include "crafting_table.hpp"
#include <string>

namespace Lib {
	void DetailsHandler();
	void GiveHandler();
	void DiscardHandler();
	void CraftingHandler();
	void GiveChecker(string name, int temp);
	void MoveHandler(string source, int slotCount);
	void MoveItemHandler(int sourceSlot,int N, int destSlot[] , bool tool, bool sourceInv, bool destInv);
	void ClearBuffer();
}

#endif