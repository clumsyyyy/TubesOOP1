#include "headers/table.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib
{
	// IMPLEMENTATION FIELD FOR PARENT CLASS: Table
	Table::Table(int row, int col) : ROWS(row), COLS(col)
	{
		this->slot = new Item * [ROWS * COLS];
		for (int i = 0; i < ROWS * COLS; i++)
			this->slot[i] = nullptr;
	}

	Table::~Table()
	{
		// delete[] this->slot;
	}


	bool Table::isIndexValid(int pos)
	{
		return (0 <= pos && pos < ROWS * COLS);
	}


    Item* Table::get(int pos) {
        if (!isIndexValid(pos)) {
            throw new InvException("INVALID");
        }
        return this->slot[pos];
    }

    Item* Table::operator[](int pos) {
        return get(pos);
    }


    void Table::set(int pos, Item* item) {
        if (!isIndexValid(pos)) {
            throw new InvException("INVALID");
        }
        if (this->slot[pos] != nullptr)
            delete this->slot[pos];
        (this->slot[pos]) = item;
    }

	void Table::specify(int pos) {
        if (!isIndexValid(pos)) {
            throw new TableException("INVALID");
        }
        slot[pos]->displayInfo();
    }
}