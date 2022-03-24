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
		/**
		 * @brief Constructor for Table class
		 * @param row Number of rows in the table
		 * @param col Number of columns in the table
		 */
		Table(int, int);
		
		/**
		 * @brief Destructor for Table class
		 */
		~Table();

		/**
		 * @brief Check if the index is valid
		 * 
		 * @param pos 
		 * @return true 
		 * @return false 
		 */
		bool isIndexValid(int);

		
		/**
		 * @brief Get the Inventory Buffer at a specific slot
		 * 
		 * @param pos Index of the slot
		 * @return Item* Pointer to the Item object
		 */
		Item* get(int pos);

		
		/**
		 * @brief Overload the [] operator to get the Inventory Buffer at a specific slot
		 * 
		 * @param pos Index of the slot
		 * @return Item* Pointer to the Item object
		 */
		Item* operator[](int);

		/**
		 * @brief set the Item at the specified position
		 * 
		 * @param pos  Index of the slot
		 * @param item Item to be set in the slot
		 */
		void set(int, Item*);

		/**
		 * @brief Display info of specific slot in inventory
		 * 
		 * @param pos 
		 */
		void specify(int);
    };

    class Inventory: public Table
	{
    public:
	    /**
		 * @brief Default Constructor for Class Inventory
		 *  Initializes the inventory with a default size of INV ROWS x INV COLS slots
		 *  Each slot (buffer) is initialized with a default Item Constructor
		 *
		 *
		 */
	    Inventory();

		
		/**
		 * @brief Overload the << operator to display the inventory layout
		 * 
		 * @param os Output Stream
		 * @param inven inventory to be displayed
		 * @return ostream& reference to the output stream
		 */
	    friend ostream& operator<<(ostream& os, Inventory* inven);

		/**
		 * @brief Overload the << operator to display the inventory details
		 * 
		 * @param os Output Stream
		 * @param inven inventory to be displayed
		 * @return ostream& reference to the output stream
		 */
	    friend ostream& operator<<(ostream& os, Inventory& inven);

		/**
		 * @brief Calculates the number of filled slots in the inventory
		 * 
		 * @return Count of filled inventory
		 */
		int filledSlots();

		/**
		 * @brief Adds a non-tool item to the inventory
		 * 
		 * @param item Non-tool item to be added
		 * @param start start index to search for slot
		 */
	    void addNonTool(NonTool* item, int start);

		/**
		 * @brief Adds a tool item to the inventory
		 * 
		 * @param item Tool item to be added
		 * @param quant Quantity of item
		 */
	    void addTool(Tool* item, int quant);

		/**
		 * @brief Discards the specified quantity of an item from the inventory
		 * 
		 * @param quant Quantity of items to be discarded
		 * @param slot Crafting table slot in which the items would like
		 * to be discarded are
		 */
	    void discard(int quant, int slot);

		/**
		 * @brief Moves an item from a slot in the inventory
		 * to a slot in the crafting table
		 * @param slotSrc source slot
		 * @param destSlot destination slot
		 * @param N quantity of item to be moved
		 */
	    void toCraft(int slotSrc, int destSlot[], int N);

		/**
		 * @brief Moves an item from one inventory slot to another
		 * 
		 * @param slotSrc source slot
		 * @param destSlot destination slot
		 */
	    void toAnotherSlot(int slotSrc, int destSlot);
    };

    class CraftingTable: public Table
	{
	public:
	    /**
		 * @brief Construct a new Crafting Table:: Crafting Table object    
		 * 
		 */
		CraftingTable();

		/**
		 * @brief Overload the << operator to print the crafting table layout
		 * 
		 * @param os 
		 * @param ct 
		 * @return ostream& 
		 */
	    friend ostream& operator<<(ostream& os, CraftingTable* ct);

		/**
		 * @brief Overload the << operator to print the crafting table details
		 * 
		 * @param os 
		 * @param ct
		 * @return ostream& 
		 */
	    friend ostream& operator<<(ostream& os, CraftingTable& ct);

		/**
		 * @brief Discards the specified quantity of an item from the crafting table
		 * 
		 * @param quant Quantity of items to be discarded
		 * @param slot Crafting table slot in which the items would like
		 * to be discarded are
		 */
	    void discard(int quant, int slot);

		/**
		 * @brief Moves an item from one inventory slot to another
		 * 
		 * @param slotSrc 
		 * @param destSlot 
		 */
	    void toInv(int slotSrc, int destSlot);
    };
}

#endif