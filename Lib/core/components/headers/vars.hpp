#ifndef VARS_HPP
#define VARS_HPP

#include <vector>
#include <string>
#include <tuple>

#define INV_COLS 9
#define INV_ROWS 3
#define INV_SIZE INV_COLS * INV_ROWS
#define CRAFT_COLS 3
#define CRAFT_ROWS 3
#define CRAFT_SIZE CRAFT_COLS * CRAFT_ROWS
#define MAX_STACK 64
#define UNDEFINED_ID -999
#define UNDEFINED_QUANTITY 999
#define WIDTH 12
#define NUMWIDTH 4
#define TupleItem tuple<string, string, string, string>
#define TupleRecipe tuple<tuple<int,int>,vector<string>,tuple<int,string>>

#endif