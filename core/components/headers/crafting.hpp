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
        int i, j;
        int n, m;
    public:
        Crafting();
        ~Crafting();
        void setStart(int i, int j);
        void setEnd(int n, int m);
        void set_crafting_table(int min);
        string getName() const;
        int getSum() const;
        void type1(tuple<int,vector<string>,tuple<int,string>> tup);
        void type2(tuple<int,vector<string>,tuple<int,string>> tup);
        void type3(tuple<int,vector<string>,tuple<int,string>> tup);
        int tools();
        void returning();
};

#endif