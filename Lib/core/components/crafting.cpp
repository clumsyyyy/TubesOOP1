#include "headers/crafting.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib {
    Crafting::Crafting() {
        this->ID = "-999"; this->name = "UNDEFINED"; this->type = "UNDEFINED"; this->btype = "UNDEFINED";
        this->row = 0; this->col = 0;
    }

    Crafting::Crafting(TupleRecipe TupRecipe) : Crafting() {
        this->TupRecipe = TupRecipe;
    }

    Crafting::~Crafting() { }

    void Crafting::set_bound(int row, int col) {
        this->row = row;
        this->col = col;
    }

    void Crafting::set_crafting_table(int min, int i, int j, bool reverse) {
        for (int idx = i; idx < this->row+i; idx++) {
            for (int idj = reverse? j+col-1 : j; reverse ? idj >= j : idj < this->col+j; reverse ? idj-- : idj++ ) {
                if (GET_CRAFT(idx, idj)->getID() != UNDEFINED_ID) {
                    gm.crftab.discard(min, CRAFT_IDX(idx, idj));
                }
            }
        }
    }

    void Crafting::set_result(const TupleItem& item) {//string ID, string name, string type, string btype) {
        this->ID = get<0>(item);
        this->name = get<1>(item);
        this->type = get<2>(item);
        this->btype = get<3>(item);
    }

    void Crafting::set_result(const Item& item) {
        this->ID = to_string(item.getID());
        this->name = item.getName();
        this->type = item.getType();
        this->btype = item.getBType();
    }

    TupleItem Crafting::get_item_result() const {
        return make_tuple(this->ID,this->name,this->type,this->btype);
    }

    int Crafting::calculate_result(int i, int j, bool reverse) {
        int min = UNDEFINED_QUANTITY;
        auto& itemsRecipe = get<1>(this->TupRecipe);
        string check;
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

    bool Crafting::is_another_space_free(int i, int j, bool reverse) {
        for (int k = 0; k < CRAFT_ROWS; k++) {
            for (int l = 0; l < CRAFT_COLS; l++) {              
                if (
                    !(i <= k && k < this->row+i
                        && (
                            reverse ? this->col+j-1 >= l
                            && l >= j : j <= l
                            && l < this->col+j
                        )
                    )
                ) {
                    if (GET_CRAFT(k, l)->getID() != UNDEFINED_ID) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    int Crafting::recipe() {
        int n = 0;
        auto& idxRecipe = get<0>(this->TupRecipe);
        auto& itemResRecipe = get<2>(this->TupRecipe);
        int itemResCntRecipe = get<3>(this->TupRecipe);

        set_bound(get<0>(idxRecipe), get<1>(idxRecipe));
        for (int i = 0; i <= CRAFT_ROWS-this->row; i++) {
            for (int j = 0; j <= CRAFT_ROWS-this->col; j++) {
                int min;
                // check recipe for each reflection
                for (bool r : { false, true }) {
                    min = calculate_result(i, j, r);
                    if (min > 0) {
                        if (this->row != 3 || this->col != 3) {
                            if (!is_another_space_free(i, j, r)) {
                                return 0;
                            }
                        }
                        n = itemResCntRecipe * min;
                        set_result(itemResRecipe);
                        this->set_crafting_table(min, i, j, r);
                        return n;
                    }
                }
            }
        } 
        return n;
    }

    int Crafting::tools() {
        int durability = 0;
        int sum = 0;
        string temp;
        for (int i = 0; i < CRAFT_SIZE; i++) {
            Item* item = gm.crftab[i];
            if (item->isNonTool()) {
                break;
            } else if (item->isTool()) {
                if (sum > 0 && temp != item->getName()) {
                    break;
                }
                temp = item->getName();
                sum++;
                set_result(*item);
                durability = min(durability + item->getDurability(), 10);
                if (sum > 2) {
                    durability = 0;
                    return -1;
                }
            }
        }
        return durability;
    }

    void Crafting::crafting_proses() {
        for (tuple tup : gm.recipeConfig) {
            int n = 0;
            TupleItem result_item;
            Crafting crf(tup);
            n = crf.recipe();
            result_item = crf.get_item_result();
            if (n > 0) {
                if (get<3>(result_item) == "NONTOOL") {
                    NonTool* NT = new NonTool(result_item, n);
                    gm.inv.addNonTool(NT, 0);
                } else if (get<3>(result_item) == "TOOL") {
                    Tool* T = new Tool(result_item, 10);
                    gm.inv.addTool(T,n);                           
                }
                cout << "crafted " << n << " " << get<1>(result_item) << endl;
                crf.returning();
                return;
            }
        }
        Crafting crf;
        int durability = crf.tools();;
        TupleItem result = crf.get_item_result();
        if (durability > 0) {
            for (int i = 0; i < CRAFT_SIZE; i++) {
                if (gm.crftab[i]->getName() == get<1>(result)) {
                    gm.crftab.discard(1,i);
                }
            }
            Tool* T = new Tool(result, durability);
            cout << "Crafted new " << get<1>(result) << "!!\nNow its durability is " << durability << endl;
            gm.inv.addTool(T,1);  
            // this->returning();
        } else if (durability == -1) {
            // this->returning();
            throw new CraftingException("TOOL");
        } else {
            // this->returning();
            throw new CraftingException("RECIPE");
        }
    }

    void Crafting::returning() {
        cout << "Returning item :" << endl;
        for (int i = 0; i < CRAFT_COLS*CRAFT_ROWS; i++) {
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