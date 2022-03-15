#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "item.hpp"
#include "inventory.hpp"
#include "crafting_table.hpp"
#include <string>


void DetailsHandler();
void GiveHandler();
void DiscardHandler();
void CraftingHandler();
void GiveChecker(string name, int temp);

#endif