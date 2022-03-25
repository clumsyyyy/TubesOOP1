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
        /**
         * @brief Construct a new Crafting object
         * 
         */
        Crafting();

        /**
         * @brief Destroy the Crafting object
         * 
         */
        ~Crafting();

        /**
         * @brief Set the bound object
         * 
         * @param row row value
         * @param col column value
         */
        void set_bound(int row, int col);

        /**
         * @brief Set the sub matrix values
         * for crafting
         * @param i row value
         * @param j column value
         */
        void set_sub_matrix(int i, int j);

        /**
         * @brief Set the crafting table minimum value
         * 
         * @param min 
         */
        void set_crafting_table(int min);

        /**
         * @brief Get the count 
         * 
         * @return int 
         */
        int get_count() const;
        int get_sum() const;

        /**
         * @brief Calculates the crafting result
         * 
         * @param reverse 
         * @return int 
         */
        int calculate_result(bool reverse);

        /**
         * @brief Checks if another space is free
         * 
         * @return true 
         * @return false 
         */
        bool is_another_space_free();

        /**
         * @brief Crafts an item from existing recipe
         * 
         * @return Item* 
         */
        Item* recipe();

        /**
         * @brief Crafts a new tool item with new durability
         * from two tool item
         * @return Item* 
         */
        Item* tools();

        /**
         * @brief Previews crafting (for GUI)
         * 
         * @return Item* 
         */
        Item* crafting_preview();

        /**
         * @brief Manages the crafting process
         * 
         */
        static void crafting_proses();
    };
}

#endif
