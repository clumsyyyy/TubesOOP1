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
	void MoveItemHandler(string sourceSlot,int N, int destSlot[], bool destInv);
	bool isToolMoved(int slot, bool invSource);
	bool isInv(char a);
	void ClearBuffer();
}

#endif