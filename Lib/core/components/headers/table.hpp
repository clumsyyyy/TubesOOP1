#ifndef SLOT_HPP
#define SLOT_HPP

#include "item.hpp"

namespace Lib {
    class Table
    {
    public:
		Item** slot;
		const int ROWS;
		const int COLS;

		Table(int, int);
		~Table();
		bool isIndexValid(int);
		Item* get(int pos);
		Item* operator[](int);
		void set(int, Item*);
		void specify(int);
    };

    class Inventory: public Table
	{
	
    public:
	    Inventory();
	    friend ostream& operator<<(ostream& os, Inventory* inven);
	    friend ostream& operator<<(ostream& os, Inventory& inven);
		int filledSlots();
	    void addNonTool(NonTool* item, int start);
	    void addTool(Tool* item, int quant);
	    void discard(int quant, int slot);
	    void toCraft(int slotSrc, int destSlot[], int N);
	    void toAnotherSlot(int slotSrc, int destSlot[]);
    };

    class CraftingTable: public Table
	{
	
	public:
		CraftingTable();
	    friend ostream& operator<<(ostream& os, CraftingTable* ct);
	    friend ostream& operator<<(ostream& os, CraftingTable& ct);
	    void discard(int quant, int slot);
	    void toInv(int slotSrc, int destSlot[]);
    };
}

#endif