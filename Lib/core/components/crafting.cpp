#include "headers/crafting.hpp"
#include "../globals.hpp"

namespace Lib {
    Crafting::Crafting() {
        this->ID = "-999";
        this->name = "UNDEFINED";
        this->type = "XXXX";
        this->btype = "XXXX";
        this->row = 0; this->col = 0;
    }

    Crafting::Crafting(TupleRecipe TupRecipe) {
        this->ID = "-999";
        this->name = "UNDEFINED";
        this->type = "XXXX";
        this->btype = "XXXX";
        this->TupRecipe = TupRecipe;
        this->row = 0; this->col = 0;
    }

    Crafting::~Crafting() { }

    void Crafting::set_bound(int row, int col) {
        this->row = row;
        this->col = col;
    }

    void Crafting::set_crafting_table(int min, int i, int j, bool reverse) {
        for (int idx = i; idx < this->row+i; idx++) {
            for (int idj = reverse? j+col : j; reverse ? idj >= this->col+j : idj < this->col+j; reverse ? idj-- : idj++ ) {
                if (crftab->get(idx*CRAFT_COLS + idj)->getName() != "UNDEFINED") {
                    crftab->discard(min, idx*CRAFT_COLS + idj);
                }
            }
        }
    }

    void Crafting::set_result(string ID, string name, string type, string btype) {
        this->ID = ID;
        this->name = name;
        this->type = type;
        this->btype = btype;
    }

    TupleItem Crafting::get_result() const {
        return make_tuple(this->ID,this->name,this->type,this->btype);
    }

    int Crafting::calculate_result(int i, int j, bool reverse) {
        int min = UNDEFINED_QUANTITY;
        string check; 
        for (int k = i, n = 0; k < this->row+i && n < this->row; k++, n++) {
            for (int l = reverse ? this->col+j-1 : j, m = 0; (reverse ? l >= j : l < this->col+j) && m < this->col; (reverse? l--: l++), m++) {
                if (crftab->get(k * CRAFT_COLS + l)->getName() != get<1>(this->TupRecipe)[n*col+m] && 
                    crftab->get(k * CRAFT_COLS + l)->getType() != get<1>(this->TupRecipe)[n*col+m]) {
                    min = 0;
                    break;
                }
                
                if (crftab->get(k * CRAFT_COLS + l)->getQuantity() < min && crftab->get(k * CRAFT_COLS + l)->getID() != UNDEFINED_ID) {
                    min = crftab->get(k * CRAFT_COLS + l)->getQuantity();
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
                
                if (!(i <= k && k < this->row+i && (reverse? this->col+j-1 >= l && l >= j : j <= l && l < this->col+j))) {
                    if (crftab->get(k*CRAFT_COLS+l)->getID() != UNDEFINED_ID) {
                        cout << k << " " << l << endl;
                        return false;
                    }
                }
            }
        }
        return true;
    }

    int Crafting::recipe() {
        int n = 0;

        set_bound(get<0>(get<0>(this->TupRecipe)),get<1>(get<0>(this->TupRecipe)));
        for (int i = 0; i <= CRAFT_ROWS-this->row; i++) {
            for (int j = 0; j <= CRAFT_ROWS-this->col; j++) {
                int min;
                // Check recipe 
                min = calculate_result(i,j,false);
                if (min > 0) {
                    if (this->row != 3 || this->col != 3) {
                        if (!is_another_space_free(i,j,false)) {
                            return 0;
                        }
                    }                    
                    name = get<1>(get<2>(this->TupRecipe));
                    n = get<3>(this->TupRecipe)*min;
                    set_result(get<0>(get<2>(this->TupRecipe)),get<1>(get<2>(this->TupRecipe)),
                               get<2>(get<2>(this->TupRecipe)),get<3>(get<2>(this->TupRecipe)));
                    this->set_crafting_table(min,i,j,true); 
                    return n;               
                }
                // Check recipe (reflection y)
                min = calculate_result(i,j,true);
                if (min > 0) {
                    if (this->row != 3 || this->col != 3) {
                        if (!is_another_space_free(i,j,true)) {
                            return 0;
                        }
                    }  
                    n = get<3>(this->TupRecipe)*min;
                    set_result(get<0>(get<2>(this->TupRecipe)),get<1>(get<2>(this->TupRecipe)),
                               get<2>(get<2>(this->TupRecipe)),get<3>(get<2>(this->TupRecipe)));
                    this->set_crafting_table(min,i,j,true); 
                    return n;
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
            if (crftab->get(i)->getBType() == "NONTOOL") {
                break;
            } else if (crftab->get(i)->getBType() == "TOOL") {
                if (sum > 0 && temp != crftab->get(i)->getName()) {
                    break;
                }
                temp = crftab->get(i)->getName();
                sum++;
                set_result(to_string(crftab->get(i)->getID()),crftab->get(i)->getName(),
                            crftab->get(i)->getType(),crftab->get(i)->getBType());
                durability = durability + crftab->get(i)->getDurability() > 10 ? 
                             10 : durability + crftab->get(i)->getDurability();
                if (sum > 2) {
                    durability = 0;
                    return -1;
                }
            }
        }
        return durability;
    }

    void Crafting::crafting_proses() {
        for (tuple tup : *recipeConfig) {
            int n = 0;
            TupleItem result;
            this->TupRecipe = tup;
            // cout << "row :" << get<0>(get<0>(tup)) << " col :" << get<1>(get<0>(tup)) << endl;
            // int i = 0;
            // for (string str: get<1>(tup)) {
            //     cout << str << " ";
            //     if (i == get<1>(get<0>(tup))-1) {
            //         cout << endl;
            //         i = 0;
            //     } else {
            //         i++;
            //     }
            // }
            // cout << "ID : " << get<0>(get<2>(tup)) << " name : " << get<1>(get<2>(tup)) << " type : " << get<2>(get<2>(tup)) << " btype : " << get<3>(get<2>(tup)) << endl;
            // cout << "Quantity : " << get<3>(tup) << endl;
            n = this->recipe();
            result = this->get_result();
            // cout << n << endl;
            if (n > 0) {
                if (get<3>(result) == "NONTOOL") {
                    NonTool* NT = new NonTool(stoi(get<0>(result)), get<1>(result), get<2>(result), get<3>(result), n);
                    inv->addNonTool(NT, 0);
                } else if (get<3>(result) == "TOOL") {
                    Tool* T = new Tool(stoi(get<0>(result)), get<1>(result), get<2>(result), get<3>(result), n);
                    inv->addTool(T);                           
                }
                cout << "crafted " << n << " " << get<1>(result) << endl;
                this->returning();
                return;
            }
        }
        int durability = this->tools();;
        TupleItem result = this->get_result();
        if (durability > 0) {
            for (int i = 0; i < CRAFT_SIZE; i++) {
                if (crftab->get(i)->getName() == name) {
                    crftab->discard(1,i);
                }

            }
            Tool* T = new Tool(stoi(get<0>(result)), get<1>(result), get<2>(result), get<3>(result), durability);
            inv->addTool(T);  
            this->returning();
        } else if (durability == -1) {
            throw "can't craft more than two tools\n";
        } else {
            this->returning();
            throw "recipe not found\n";
        }
    }

    void Crafting::returning() {
        cout << "returning item :" << endl;
        for (int i = 0; i < CRAFT_COLS*CRAFT_ROWS; i++) {
            if (crftab->get(i)->getQuantity() > 0) {
                if (crftab->get(i)->getType() == "NONTOOL") {
                    NonTool *NT = new NonTool(crftab->get(i)->getID(),
                                            crftab->get(i)->getName(),
                                            crftab->get(i)->getBType(),
                                            crftab->get(i)->getType(),
                                            crftab->get(i)->getQuantity());
                    inv->addNonTool(NT, 0);
                } else {
                    Tool *T = new Tool(crftab->get(i)->getID(),
                                            crftab->get(i)->getName(),
                                            crftab->get(i)->getBType(),
                                            crftab->get(i)->getType(),
                                            crftab->get(i)->getDurability());
                    inv->addTool(T, 1);
                }
            } 
            crftab->discard(crftab->get(i)->getQuantity(),i);
        }
    }
}