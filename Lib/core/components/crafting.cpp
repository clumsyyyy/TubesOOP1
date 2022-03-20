#include "headers/crafting.hpp"
#include "headers/GameManager.hpp"
#include "../globals.hpp"

namespace Lib {
    Crafting::Crafting() {
        this->ID = "-999"; this->name = "UNDEFINED"; this->type = "UNDEFINED"; this->btype = "UNDEFINED";
        this->row = 0; this->col = 0;
    }

    Crafting::Crafting(TupleRecipe TupRecipe) {
        this->ID = "-999"; this->name = "UNDEFINED"; this->type = "UNDEFINED"; this->btype = "UNDEFINED";
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
            for (int idj = reverse? j+col-1 : j; reverse ? idj >= j : idj < this->col+j; reverse ? idj-- : idj++ ) {
                if (crftab->get(idx*CRAFT_COLS + idj)->getID() != UNDEFINED_ID) {
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

    TupleItem Crafting::get_item_result() const {
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
                    this->set_crafting_table(min,i,j,false); 
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
            if (crftab->get(i)->isNonTool()) {
                break;
            } else if (crftab->get(i)->isTool()) {
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
        for (tuple tup : GameManager::getInstance().recipeConfig) {
            int n = 0;
            TupleItem result_item;
            Crafting crf(tup);
            n = crf.recipe();
            result_item = crf.get_item_result();
            if (n > 0) {
                if (get<3>(result_item) == "NONTOOL") {
                    NonTool* NT = new NonTool(stoi(get<0>(result_item)), get<1>(result_item), get<2>(result_item), get<3>(result_item), n);
                    inv->addNonTool(NT, 0);
                } else if (get<3>(result_item) == "TOOL") {
                    int durability;
                    string kind;
                    istringstream iss(get<1>(result_item));
                    getline(iss,kind,'_');
                    if (kind == "WOODEN") {
                        durability = 4;
                    } else if (kind == "STONE") {
                        durability = 6;
                    } else if (kind == "IRON") {
                        durability = 8;
                    } else if (kind == "DIAMOND") {
                        durability = 10;
                    } else {
                        durability = 0;
                    }
                    Tool* T = new Tool(stoi(get<0>(result_item)), get<1>(result_item), get<2>(result_item), get<3>(result_item), durability);
                    inv->addTool(T,n);                           
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
                if (crftab->get(i)->getName() == get<1>(result)) {
                    crftab->discard(1,i);
                }
            }
            Tool* T = new Tool(stoi(get<0>(result)), get<1>(result), get<2>(result), get<3>(result), durability);
            cout << "Crafted new " << get<1>(result) << "!!\nNow its durability is " << durability << endl;
            inv->addTool(T,1);  
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
            if (crftab->get(i)->getID() != UNDEFINED_ID) {
                if (crftab->get(i)->isNonTool()) {
                    NonTool *NT = new NonTool(crftab->get(i)->getID(),
                                            crftab->get(i)->getName(),
                                            crftab->get(i)->getType(),
                                            crftab->get(i)->getBType(),
                                            crftab->get(i)->getQuantity());
                    inv->addNonTool(NT, 0);
                    crftab->discard(crftab->get(i)->getQuantity(),i);
                } else if (crftab->get(i)->isTool()) {
                    Tool *T = new Tool(crftab->get(i)->getID(),
                                            crftab->get(i)->getName(),
                                            crftab->get(i)->getType(),
                                            crftab->get(i)->getBType(),
                                            crftab->get(i)->getDurability());
                    inv->addTool(T, 1);
                    crftab->discard(crftab->get(i)->getQuantity(),i);
                }
            }           
        }
    }
}