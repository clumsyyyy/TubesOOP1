#ifndef VARS_HPP
#define VARS_HPP

#include <vector>
#include <string>
#include <tuple>

constexpr auto INV_COLS = 9;
constexpr auto INV_ROWS = 3;
#define INV_SIZE INV_COLS * INV_ROWS
#define INV_IDX(i,j) (i * INV_COLS + j)
#define GET_INV(i,j) gm.inv[INV_IDX(i,j)]
constexpr auto CRAFT_COLS = 3;
constexpr auto CRAFT_ROWS = 3;
#define CRAFT_SIZE CRAFT_COLS * CRAFT_ROWS
#define CRAFT_IDX(i,j) (i * CRAFT_COLS + j)
#define GET_CRAFT(i,j) gm.crftab[CRAFT_IDX(i,j)]
constexpr auto MAX_STACK = 64;
constexpr auto UNDEFINED_QUANTITY = 999;
constexpr auto MAX_DURABILITY = 10;
constexpr auto WIDTH = 12;
constexpr auto NUMWIDTH = 4;
constexpr auto UNDEFINED = "UNDEFINED";
#define TupleItem tuple<string, string, string, string>
#define TupleRecipe tuple<tuple<int,int>,vector<string>,TupleItem,int>

#endif