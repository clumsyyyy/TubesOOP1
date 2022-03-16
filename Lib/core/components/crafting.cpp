#include "headers/crafting.hpp"
#include "../globals.hpp"

Crafting::Crafting() {
    this->i = 0; this->j = 0;
    this->n = 0;this->m = 0;

    this->name = "UNDEFINED";
    this->sum = 0;
}

Crafting::Crafting(TupleRecipe TupRecipe) {
    this->i = 0; this->j = 0;
    this->n = 0;this->m = 0;
    this->TupRecipe = TupRecipe;
    
    this->name = "UNDEFINED";
    this->sum = 0;
}

Crafting::~Crafting() { }

void Crafting::setStart(int i, int j) {
    this->i = i;
    this->j = j;
}

void Crafting::setEnd(int n, int m) {
    this->n = n;
    this->m = m;
}

void Crafting::set_crafting_table(int min) {
    bool flag = this->j < this-> m;
    for (int idx = this->i; idx < this->n; idx++) {
        for (int idj = this->j; flag? idj < this->m : idj >= this->m; flag? idj++ : idj--) {
            if (crftab->get(idx*CRAFT_COLS + idj)->getName() != "UNDIFINED") {
                crftab->get(idx*CRAFT_COLS + idj)->setQuantity(
                    crftab->get(idx*CRAFT_COLS + idj)->getQuantity()-min >= 0 ?
                        crftab->get(idx*CRAFT_COLS + idj)->getQuantity()-min:0);
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

void Crafting::recipe() {
    int row = get<0>(get<0>(this->TupRecipe));
    int col = get<1>(get<0>(this->TupRecipe));
    for (int i = 0; i <= CRAFT_ROWS-row; i++) {
        for (int j = 0; j <= CRAFT_ROWS-col; j++) {
            int min = UNDEFINED_QUANTITY, count = 0;
            string check; 
            // Check recipe
            for (int k = i, n = 0; k < row+i && n < row; k++, n++) {
                for (int l = j, m = 0; l < col+j && m < col; l++, m++) {
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
            if (min > 0) {
                name = get<1>(get<2>(this->TupRecipe));
                sum += get<0>(get<2>(this->TupRecipe))*min;
                this->setStart(i,j);
                this->setEnd(row+i,col+j);
                this->set_crafting_table(min);                
            }
            min = UNDEFINED_QUANTITY, count = 0; 
            // Check recipe (reflection y)
            for (int k = i, n = 0; k < row+i && n < row; k++, n++) {
                for (int l = col+j-1, m = 0; l >= j && m < col; l--, m++) {
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
            if (min > 0) {
                name = get<1>(get<2>(this->TupRecipe));
                sum += get<0>(get<2>(this->TupRecipe))*min;
                this->setStart(i,col+j);
                this->setEnd(row+i,j);
                this->set_crafting_table(min);
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