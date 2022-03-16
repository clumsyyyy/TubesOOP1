#include "headers/crafting.hpp"
#include "../globals.hpp"

Crafting::Crafting() {
    this->name = "UNDEFINED";
    this->sum = 0;
    this->row = 0; this->col = 0;
}

Crafting::Crafting(TupleRecipe TupRecipe) {
    this->name = "UNDEFINED";
    this->sum = 0;
    this->TupRecipe = TupRecipe;
    this->row = 0; this->col = 0;
}

Crafting::~Crafting() { }

void Crafting::setBound(int row, int col) {
    this->row = row;
    this->col = col;
}

void Crafting::set_crafting_table(int min, int i, int j, bool reverse) {
    // cout << start << " " << endl;
    // int i = start / CRAFT_COLS, j = start % (CRAFT_COLS);
    // int n = end / CRAFT_COLS, m = end % (CRAFT_COLS);
    for (int idx = i; idx < this->row+i; idx++) {
        for (int idj = reverse? j+col : j; reverse ? idj >= this->col+j : idj < this->col+j; reverse ? idj-- : idj++ ) {
            if (crftab->get(idx*CRAFT_COLS + idj)->getName() != "UNDIFINED") {
                if (crftab->get(idx*CRAFT_COLS + idj)->getQuantity()-min > 0) {
                    crftab->get(idx*CRAFT_COLS + idj)->setQuantity(crftab->get(idx*CRAFT_COLS + idj)->getQuantity()-min);
                } else {
                    crftab->set(idx*CRAFT_COLS + idj, new Item());
                }
            }
        }
    }
}

string Crafting::getName() const {
    return this->name;
}
int Crafting::getSum() const {
    return this->sum;
}
int Crafting::calculateResult(int i, int j, bool reverse) const {
    int min = UNDEFINED_QUANTITY, count = 0;
    string check; 
    // cout << "Masuk" << endl;
    for (int k = i, n = 0; k < this->row+i && n < this->row; k++, n++) {
        for (int l = reverse ? col+j-1 : j, m = 0; (reverse ? l >= j : l < this->col+j) && m < this->col; (reverse? l--: l++), m++) {
            if (crftab->get(k * CRAFT_COLS + l)->getName() != get<1>(this->TupRecipe)[n*col+m]) {
                if (crftab->get(k * CRAFT_COLS + l)->getBType() != get<1>(this->TupRecipe)[n*col+m]) {
                    min = 0;
                    break;
                } else {
                    if (count == 0) {
                        check = crftab->get(k * CRAFT_COLS + l)->getName();
                    }
                    count++;
                }    
            }
            // check name (if recipe using btype)
            if (count > 0 && check != crftab->get(k * CRAFT_COLS + l)->getName()) {
                min = 0;
                break;
            }
            if (crftab->get(k * CRAFT_COLS + l)->getQuantity() < min && crftab->get(k * CRAFT_COLS + l)->getName() != "UNDEFINED") {
                min = crftab->get(k * CRAFT_COLS + l)->getQuantity();
            }
        }
        if (min == 0) {
            break;
        }
    }
    return min;
}

void Crafting::recipe() {
    int row = get<0>(get<0>(this->TupRecipe));
    int col = get<1>(get<0>(this->TupRecipe));
    setBound(row,col);
    for (int i = 0; i <= CRAFT_ROWS-row; i++) {
        for (int j = 0; j <= CRAFT_ROWS-col; j++) {
            int min;
            // Check recipe 
            min = calculateResult(i,j,false);
            if (min > 0) {
                name = get<1>(get<2>(this->TupRecipe));
                sum += get<0>(get<2>(this->TupRecipe))*min;
                this->set_crafting_table(min,i,j,false);                
            }
            // Check recipe (reflection y)
            min = calculateResult(i,j,true);
            if (min > 0) {
                name = get<1>(get<2>(this->TupRecipe));
                sum += get<0>(get<2>(this->TupRecipe))*min;
                this->set_crafting_table(min,i,j,true); 
            }
        }
    } 
}

int Crafting::tools() {
    int durability = 0;
    for (int i = 0; i < CRAFT_SIZE; i++) {
        if (crftab->get(i)->getType() == "NONTOOL") {
            break;
        } else if (crftab->get(i)->getType() == "TOOL") {
            if (sum > 0 && name != crftab->get(i)->getName()) {
                break;
            }
            this->sum++;
            this->name = crftab->get(i)->getName();
            durability += crftab->get(i)->getDurability();
            if (this->sum > 2) {
                break;
            }
        }
        
    }
    return durability;
}

void Crafting::returning() {
    for (int i = 0; i < CRAFT_COLS*CRAFT_ROWS; i++) {
        // int i = idx % INV_ROWS;
        // int j = idx / INV_ROWS;
        if (crftab->get(i)->getQuantity() > 0) {
            if (crftab->get(i)->getType() == "NONTOOL") {
                NonTool *NT = new NonTool(crftab->get(i)->getID(),
                                           crftab->get(i)->getName(),
                                           crftab->get(i)->getType(),
                                           crftab->get(i)->getBType(),
                                           crftab->get(i)->getQuantity());
                inv->addNonTool(NT);
            } else {
                Tool *T = new Tool(crftab->get(i)->getID(),
                                          crftab->get(i)->getName(),
                                          crftab->get(i)->getType(),
                                          crftab->get(i)->getBType(),
                                          crftab->get(i)->getDurability());
                inv->addTool(T);
            }
        } 
        crftab->discard(crftab->get(i)->getQuantity(),i);
    }
}