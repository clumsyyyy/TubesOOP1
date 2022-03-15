#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "item.hpp"
#include "inventory.hpp"
#include "vars.hpp"
#include <string>


void DetailsHandler();
void GiveHandler();
void DiscardHandler();
void GiveChecker(string name, int temp);

#endif