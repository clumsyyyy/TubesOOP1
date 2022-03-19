#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "vars.hpp"
#include "item.hpp"
#include "iostream"
#include <tuple>
#include <vector>
#include <sstream>
#include <string>

namespace Lib {
    using namespace std;

    class Crafting {
    private:
        string ID, name, type, btype;
        TupleRecipe TupRecipe;
        int row, col;
    public:
        Crafting();
        Crafting(TupleRecipe TupRecipe);
        ~Crafting();
        void set_bound(int row, int col);
        void set_crafting_table(int min, int i, int j, bool reverse);
        void set_result(string ID, string name, string btype, string type);
        TupleItem get_item_result() const;
        int calculate_result(int i, int j, bool reverse);
        bool is_another_space_free(int i, int j, bool reverse);
        int recipe();
        int tools();
        static void crafting_proses();
        void returning();
    };
}

#endif