#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "vars.hpp"
#include "item.hpp"
#include "iostream"
#include <tuple>
#include <vector>
#include <string>

namespace Lib {
    using namespace std;

    class Crafting {
    private:
        string name;
        int sum;
        TupleRecipe TupRecipe;
        int row, col;
    public:
        Crafting();
        Crafting(TupleRecipe TupRecipe);
        ~Crafting();
        void setBound(int row, int col);
        void set_crafting_table(int min, int i, int j, bool reverse);
        string getName() const;
        int getSum() const;
        int calculateResult(int i, int j, bool reverse) const;
        void recipe();
        int tools();
        void returning();
    };
}

#endif