#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "vars.hpp"
#include "item.hpp"
#include "iostream"
#include <tuple>
#include <vector>
#include <string>

using namespace std;

class Crafting {
    private:
        string name;
        int sum;
        TupleRecipe TupRecipe;

        int i, j;
        int n, m;
    public:
        Crafting();
        Crafting(TupleRecipe TupRecipe);
        ~Crafting();
        void setStart(int i, int j);
        void setEnd(int n, int m);
        void set_crafting_table(int min);
        string getName() const;
        int getSum() const;
        void recipe();
        int tools();
        void returning();
};

#endif