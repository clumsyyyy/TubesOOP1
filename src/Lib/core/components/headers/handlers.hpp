#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "item.hpp"
#include "table.hpp"
#include <string>

namespace Lib {
	// Handler classes handle the usage of a method and manage 
	// corresponding exceptions
    /**
     * @brief Show current inventory and crafting table item info
     *  
     * 
     * @param mode "ALL" = show all items, "ITEM" = specific item info
     * @param slot_id Slot ID
     */
	void DetailsHandler(string mode, int slot_id);

    /**
     * @brief Invoke GiveChecker to check if the item can be given
     *  
     * 
     * @param name Item Name
     * @param qty Item Quantity
     */
	void GiveHandler(string name, int qty);

    /**
     * @brief Checking if the item can be given (valid)
     *  Valid when name and quantity of the item are valid 
     *  
     * 
     * @param name Item name
     * @param qty Item quantity
     */
	void GiveChecker(string name, int temp);

    /**
     * @brief Discard spesific item from the Inventory
     * 
     * @param slot Inventory slot ID to be discarded
     * @param qty Quantity of the item to be discarded
     */
	void DiscardHandler(int index, int qty);


    /**
     * @brief Decrease durability of the tool item by 1
     * 
     * @param slot Inventory slot ID to be used (Must be a tool item)
     */
	void UseHandler(string slot);
	
    /**
     * @brief Invoke crafting_proses to craft the current items in the crafting table
     * 
     */
	void CraftingHandler();

	/**
	 * @brief Handles the moving process for different scenarios
	 * 
	 * @param source source table of moving
	 * @param slotCount slot count
	 */
	void MoveHandler(string source, int slotCount, vector<string>);

	
    /**
     * @brief Moving item from a slot to another slot
     * 
     * @param source 
     * @param slotCount 
     * @param slotDestV 
     */
	void MoveItemHandler(string sourceSlot,int N, int destSlot[], bool destInv);

	/**
     * @brief Export inventory state to a file
     * 
     * @param path 
     */
	void ExportHandler(string path);

     void ClearBuffer();
}

#endif