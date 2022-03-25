#include "headers/crafting.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib {
    Crafting::Crafting() {
        this->count = 0; this->sum = 0;
        this->i_sub = 0; this->j_sub = 0;
        this->row = 0; this->col = 0;
    }

    Crafting::~Crafting() { }

    void Crafting::set_bound(int row, int col) {
        this->row = row;
        this->col = col;
    }

    void Crafting::set_sub_matrix(int i, int j) {
        this->i_sub = i;
        this->j_sub = j;
    }

    void Crafting::set_crafting_table(int min) {
        int i = this->i_sub, j = this->j_sub;
        for (int index = i; index < this->row+i; index++) {
            for (int idj = j; idj < this->col+j; idj++ ) {
                if (GET_CRAFT(index, idj) != nullptr) {
                    gm.crftab.discard(min, CRAFT_IDX(index, idj));
                }
            }
        }
    }

    int Crafting::get_count() const {
        return this->count;
    }

    int Crafting::get_sum() const {
        return this->sum;
    }

    int Crafting::calculate_result(bool reverse) {
        int min = UNDEFINED_QUANTITY;
        auto& itemsRecipe = get<1>(this->TupRecipe);
        int i = i_sub, j = j_sub;
        for (int k = i, n = 0; k < this->row+i && n < this->row; k++, n++) {
            for (
                int l = reverse ? this->col+j-1 : j, m = 0;
                (reverse ? l >= j : l < this->col+j) && m < this->col;
                (reverse? l--: l++), m++
            ) {
                Item* item = GET_CRAFT(k, l);
                // if recipe undefined and item nullptr
                // or item is defined but different than recipe
                string comp1 = UNDEFINED, comp2 = UNDEFINED;
                if (item != nullptr) {
                    comp1 = item->getName();
                    comp2 = item->getType();
                    int qty = NonTool::FromItem(item).getQuantity();
                    if (qty < min)
                        min = qty;
                }
                int idx = n * col + m;
                if (comp1 != itemsRecipe[idx] &&
                    comp2 != itemsRecipe[idx]) {
                    min = 0;
                    break;
                }
            }
            if (min == 0)
                break;
        }
        return min;
    }

    bool Crafting::is_another_space_free() {
        int i = this->i_sub, j = this->j_sub;
        for (int k = 0; k < CRAFT_ROWS; k++) {
            for (int l = 0; l < CRAFT_COLS; l++) {              
                if (!(i <= k && k < this->row+i && j <= l && l < this->col+j)) {
                    if (GET_CRAFT(k, l) != nullptr) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    Item* Crafting::recipe() {
        auto& indexRecipe = get<0>(this->TupRecipe);
        auto& itemResRecipe = get<2>(this->TupRecipe);
        int itemResCntRecipe = get<3>(this->TupRecipe);

        set_bound(get<0>(indexRecipe), get<1>(indexRecipe));
        for (int i = 0; i <= CRAFT_ROWS-this->row; i++) {
            for (int j = 0; j <= CRAFT_ROWS-this->col; j++) {
                int min;
                set_sub_matrix(i,j);
                for (bool r : { false, true }) {
                    min = calculate_result(r);
                    if (min > 0) {
                        if (this->row != 3 || this->col != 3) {
                            if (!is_another_space_free()) {
                                return nullptr;
                            }
                        }
                        this->count = min;
                        this->sum = min*itemResCntRecipe;
                        if (get<3>(itemResRecipe) == "TOOL") {
                            return new Tool(itemResRecipe);
                        } else if (get<3>(itemResRecipe) == "NONTOOL") {
                            return new NonTool(itemResRecipe, this->sum);
                        }
                    }
                }
            }
        } 
        return nullptr;
    }

    Item* Crafting::tools() {
        int durability = 0;
        int sum_tool = 0;
        Tool* tool = nullptr;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = gm.crftab[i];
            if (item != nullptr) {
                if (item->isNonTool()) {
                    return nullptr;
                }
                else if (item->isTool()) {
                    Tool& t = Tool::FromItem(item);
                    if (sum_tool == 0)
                        tool = new Tool(t);
                    else if (tool->getName() != item->getName()) {
                        delete tool; // cleanup
                        return nullptr;
                    }
                    sum_tool++;
                    if (sum_tool > 2) {
                        this->count = -2;
                        delete tool; // cleanup
                        return nullptr;
                    }
                    durability = min(durability + t.getDurability(), MAX_DURABILITY);
                }
            }
        }
        if (sum_tool == 1) {
            this->count = -1;
            delete tool; // cleanup
            return nullptr;
        }
        this->count = 1;
        this->set_sub_matrix(0, 0);
        this->set_bound(CRAFT_ROWS, CRAFT_COLS);
        if (tool != nullptr)
            tool->setDurability(durability);
        return tool;
    }

    Item* Crafting::crafting_preview() {
        // Crafting from Recipe
        for (tuple tup : gm.recipeConfig) {
            this->TupRecipe = tup;
            Item* result_item = this->recipe();
            if (result_item != nullptr)
                return result_item;
        }
        // Crafting to combine item durability
        Item* result_item = this->tools();
        if (result_item != nullptr) {
            this->set_sub_matrix(0,0);
            this->count = 1;
            this->sum = 1;
            return result_item; 
        }
        return nullptr;
    }

    void Crafting::crafting_proses() {
        Crafting crf;
        Item* item = crf.crafting_preview();
        int count = crf.get_count();
        if (count == -1) {
            throw new CraftingException("TOOL1");
        }
        else if (count == -2) {
            throw new CraftingException("TOOL2");
        }
        else if (item == nullptr) {
            throw new CraftingException("RECIPE");
        }
        int sum = crf.get_sum();
        if (item->isNonTool()) {
            cout << "Item " << item->getName() << " successfully crafted! (Quantity: "
                << sum << ") " << endl;
            gm.inv.addNonTool((NonTool*)item, 0);
        } else {
            cout << "Tool " << item->getName() << " successfully crafted! (Durability: "
                << Tool::FromItem(item).getDurability() << ") " << endl;
            gm.inv.addTool((Tool*)item, sum);
        }
        crf.set_crafting_table(count);
    }
}