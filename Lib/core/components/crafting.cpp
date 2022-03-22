#include "headers/crafting.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib {
    Crafting::Crafting() {
        // this->ID = "-999"; this->name = "UNDEFINED"; this->type = "UNDEFINED"; this->btype = "UNDEFINED";
        this->count = 0; this->sum = 0;
        this->i_sub = 0; this->j_sub = 0;
        this->row = 0; this->col = 0;
    }

    // Crafting::Crafting(TupleRecipe TupRecipe) : Crafting() {
    //     this->TupRecipe = TupRecipe;
    // }

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
                if (!GET_CRAFT(index, idj)->isUndef()) {
                    gm.crftab.discard(min, CRAFT_IDX(index, idj));
                }
            }
        }
    }
    // Monumen
    // void Crafting::set_result(const TupleItem& item) {//string ID, string name, string type, string btype) {
    //     this->ID = get<0>(item);
    //     this->name = get<1>(item);
    //     this->type = get<2>(item);
    //     this->btype = get<3>(item);
    // }

    // void Crafting::set_result(const Item& item) {
    //     this->ID = to_string(item.getID());
    //     this->name = item.getName();
    //     this->type = item.getType();
    //     this->btype = item.getBType();
    // }

    // TupleItem Crafting::get_item_result() const {
    //     return make_tuple(this->ID,this->name,this->type,this->btype);
    // }

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
                if (item->getName() != itemsRecipe[n*col+m]
                    && item->getType() != itemsRecipe[n*col+m]
                ) {
                    min = 0;
                    break;
                }
                if (item->getQuantity() < min
                    && item->getID() != UNDEFINED_ID
                ) {
                    min = item->getQuantity();
                }
            }
            if (min == 0) {
                break;
            }
        }
        return min;
    }

    bool Crafting::is_another_space_free() {
        int i = this->i_sub, j = this->j_sub;
        for (int k = 0; k < CRAFT_ROWS; k++) {
            for (int l = 0; l < CRAFT_COLS; l++) {              
                if (!(i <= k && k < this->row+i && j <= l && l < this->col+j)) {
                    if (GET_CRAFT(k, l)->getID() != UNDEFINED_ID) {
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
                                return new Item();
                            }
                        }
                        this->count = min;
                        this->sum = min*itemResCntRecipe;
                        if (get<3>(itemResRecipe) == "TOOL") {    
                            return new Tool(itemResRecipe,10);
                        } else if (get<3>(itemResRecipe) == "NONTOOL") {
                            return new NonTool(itemResRecipe,this->sum);
                        }
                    }
                }
            }
        } 
        return new Item();
    }

    Item* Crafting::tools() {
        int durability = 0;
        int sum_tool = 0;
        Tool* tool = (Tool*)new Item();
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = gm.crftab[i];
            if (item->isNonTool()) {
                return new Item();
            } else if (item->isTool()) {
                if (sum_tool > 0 && tool->getName() != item->getName()) {
                    //this->count++;
                    return new Item();
                }
                tool = (Tool*)item;
                sum_tool++;
                durability = min(durability + item->getDurability(), 10);
                if (sum_tool > 2) {
                    return new Item();
                }
            }
        }
        this->count++;
        if (sum_tool != 2) {
            return new Item();
        }
        this->set_bound(CRAFT_ROWS, CRAFT_COLS);
        this->set_sub_matrix(0, 0);
        tool->setDurability(durability);
        return tool;
    }

    Item* Crafting::crafting_preview() {
        for (tuple tup : gm.recipeConfig) {
            this->TupRecipe = tup;
            Item* result_item = this->recipe();
            if (!result_item->isUndef()) {
                if (result_item->isNonTool()) {
                    return result_item;
                } else if (result_item->isTool()) {
                    return result_item;                       
                }                
            }
        }
        Item* result_item = this->tools();
        if (!result_item->isUndef()) {
            this->set_sub_matrix(0,0);
            this->count = 1;
            this->sum = 1;
            return result_item; 
        }
        this->count = -1;
        return new Item();
    }

    void Crafting::crafting_proses() {
        Crafting crf;
        Item* item = crf.crafting_preview();
        int count = crf.get_count();
        int sum = crf.get_sum();
        if (item->isNonTool()) {
            cout << "crafted " << sum << " " << item->getName() << endl;
            gm.inv.addNonTool((NonTool*)item,0);
            crf.set_crafting_table(count);
        } else if (item->isTool()) {
            cout << "crafted " << sum << " " << item->getName() << " with durability " << item->getDurability() << endl;
            gm.inv.addTool((Tool*)item,sum);
            crf.set_crafting_table(count);
        } else if (count == -1) {
            throw new CraftingException("RECIPE");
        } else if (item->isUndef()) {
            throw new CraftingException("TOOL");
        }
    }

    void Crafting::returning() {
        cout << "Returning item :" << endl;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = gm.crftab[i];
            if (item->getID() != UNDEFINED_ID) {
                if (item->isNonTool()) {
                    NonTool *NT = new NonTool(*((NonTool*)item));
                    gm.inv.addNonTool(NT, 0);
                    gm.crftab.discard(item->getQuantity(), i);
                } else if (item->isTool()) {
                    Tool *T = new Tool(*((Tool*)item));
                    gm.inv.addTool(T, 1);
                    gm.crftab.discard(item->getQuantity(), i);
                }
            }           
        }
    }
}