#include "headers/table.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib
{
	// IMPLEMENTATION FIELD FOR PARENT CLASS: Table
	
	/**
	 * @brief Constructor for Table class
	 * @param row Number of rows in the table
	 * @param col Number of columns in the table
	 */
	Table::Table(int row, int col) : ROWS(row), COLS(col)
	{
		this->slot = new Item * [ROWS * COLS];
		for (int i = 0; i < ROWS * COLS; i++) {
			this->slot[i] = new Item();
		}
	}

	/**
	 * @brief Destructor for Table class
	 */
	Table::~Table()
	{
		delete[] this->slot;
	}

	/**
	 * @brief Check if the index is valid
	 * 
	 * @param pos 
	 * @return true 
	 * @return false 
	 */
	bool Table::isIndexValid(int pos)
	{
		return (0 <= pos && pos < ROWS * COLS);
	}


	/**
     * @brief Get the Inventory Buffer at a specific slot
     * 
     * @param pos Index of the slot
     * @return Item* Pointer to the Item object
     */

    Item* Table::get(int pos) {
        if (!isIndexValid(pos)) {
            throw new InvException("INVALID");
        }
        return this->slot[pos];
    }

	/**
     * @brief Overload the [] operator to get the Inventory Buffer at a specific slot
     * 
     * @param pos Index of the slot
     * @return Item* Pointer to the Item object
     */
    Item* Table::operator[](int pos) {
        return get(pos);
    }

	/**
     * @brief set the Item at the specified position
     * 
     * @param pos  Index of the slot
     * @param item Item to be set in the slot
     */
    void Table::set(int pos, Item* item) {
        if (!isIndexValid(pos)) {
            throw new InvException("INVALID");
        }
        if (this->slot[pos] != nullptr) {
            delete this->slot[pos];
        }
        (this->slot[pos]) = item;
    }

	/**
     * @brief Display info of specific slot in inventory
     * 
     * @param pos 
     */
	void Table::specify(int pos) {
        if (!isIndexValid(pos)) {
            throw new TableException("INVALID");
        }
        slot[pos]->displayInfo();
    }   





}