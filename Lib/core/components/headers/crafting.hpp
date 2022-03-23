#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "vars.hpp"
#include "item.hpp"
#include "iostream"
#include <tuple>
#include <vector>

namespace Lib {
    using namespace std;

    class Crafting {
    private:
        // string ID, name, type, btype;
        TupleRecipe TupRecipe;
        int i_sub, j_sub;
        int row, col;
        int count, sum;
    public:
        Crafting();
        ~Crafting();
        void set_bound(int row, int col);
        void set_sub_matrix(int i, int j);
        void set_crafting_table(int min);
        int get_count() const;
        int get_sum() const;
        int calculate_result(bool reverse);
        bool is_another_space_free();
        Item* recipe();
        Item* tools();
        Item* crafting_preview();
        static void crafting_proses();
        // void returning();
    };
}

#endif
