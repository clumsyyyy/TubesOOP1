#include "headers/crafting.hpp"
#include "../globals.hpp"

Crafting::Crafting() {
    this->i = 0;
    this->j = 0;
    this->n = 0;
    this->m = 0;
    this->name = "UNDIFINED";
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
    for (this->i; this->i < this->n; this->i++) {
        for (this->j; flag? this->j < this->m : this->j >= this->m; flag? this->j++ : this->j--) {
            if (crftab->get(i).getName() != "UNDIFINED") {
                crftab->get(i).setQuantity(crftab->get(i).getQuantity()-min);
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

void Crafting::recipe(tuple<tuple<int,int>,vector<string>,tuple<int,string>> tup) {
    int row = get<0>(get<0>(tup));
    int col = get<1>(get<0>(tup));
    for (int i = 0; i <= CRAFT_ROWS-row; i++) {
        for (int j = 0; j <= CRAFT_ROWS-col; j++) {
            int min = UNDEFINED_QUANTITY, count = 0;
            string check; 
            // Check recipe
            for (int k = i, n = 0; k < row+i && n < row; k++, n++) {
                for (int l = j, m = 0; l < col+j && m < col; l++, m++) {
                    if (crftab->get(k * CRAFT_COLS + l).getName() != get<1>(tup)[n*col+m]) {
                        if (crftab->get(k * CRAFT_COLS + l).getBType() != get<1>(tup)[n*col+m]) {
                            min = 0;
                            break;
                        } else {
                            if (count == 0) {
                            check = crftab->get(k * CRAFT_COLS + l).getName();
                            }
                            count++;
                        }
                        
                    }
                    // check name (if recipe using btype)
                    if (count > 0 && check != crftab->get(k * CRAFT_COLS + l).getName()) {
                        min = 0;
                        break;
                    }

                    if (crftab->get(i * CRAFT_COLS + j).getQuantity() < min) {
                        min = crftab->get(i * CRAFT_COLS + j).getQuantity();
                    }
                }
                if (min == 0) {
                    break;
                }
            }
            if (min > 0) {
                name = get<1>(get<2>(tup));
                sum += get<0>(get<2>(tup))*min;
                this->setStart(i,j);
                this->setEnd(row+i,col+j);
                this->set_crafting_table(min);
            }
            min = UNDEFINED_QUANTITY, count = 0; 
            // Check recipe (reflection y)
            for (int k = i, n = 0; k < row+i && n < row; k++, n++) {
                for (int l = col+j-1, m = 0; l >= j && m < col; l--, m++) {
                    if (crftab->get(k * CRAFT_COLS + l).getName() != get<1>(tup)[n*col+m]) {
                        if (crftab->get(k * CRAFT_COLS + l).getBType() != get<1>(tup)[n*col+m]) {
                            min = 0;
                            break;
                        } else {
                            if (count == 0) {
                            check = crftab->get(k * CRAFT_COLS + l).getName();
                            }
                            count++;
                        }
                        
                    }
                    // check name (if recipe using btype)
                    if (count > 0 && check != crftab->get(k * CRAFT_COLS + l).getName()) {
                        min = 0;
                        break;
                    }

                    if (crftab->get(i * CRAFT_COLS + j).getQuantity() < min) {
                        min = crftab->get(i * CRAFT_COLS + j).getQuantity();
                    }
                }
                if (min == 0) {
                    break;
                }
            } 
            if (min > 0) {
                name = get<1>(get<2>(tup));
                sum += get<0>(get<2>(tup))*min;
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
        if (crftab->get(i).getType() == "NONTOOL") {
            break;
        } else if (crftab->get(i).getType() == "TOOL") {
            if (sum > 0 && name != crftab->get(i).getName()) {
                break;
            }
            this->sum++;
            this->name = crftab->get(i).getName();
            durability += crftab->get(i).getDurability();
            if (this->sum > 2) {
                break;
            }
        }
        
    }
    return durability;
}

void Crafting::returning() {
    for (int idx = 0; idx < CRAFT_COLS*CRAFT_ROWS; idx++) {
        // int i = idx % INV_ROWS;
        // int j = idx / INV_ROWS;
        crftab->discard(crftab->get(i).getQuantity(), idx);
        if (inv->get(i).getName() == "UNDEFINED") {
            Item* temp = new Item(crftab->get(i));
            inv->set(i, temp);
        } else {
            if (inv->get(i).getName() == crftab->get(i).getName()) {
                Item* temp = new Item(crftab->get(i));
                temp->setQuantity(temp->getQuantity()+inv->get(i).getQuantity());
                inv->set(i, temp);
            } else {
                Item* temp = new Item(crftab->get(i));
                for (int i = 0; i < INV_ROWS; i++) {
                    for (int j = 0; j < INV_COLS; j++) {
                        if (inv->get(i).getName() == "UNDEFINED") {
                            inv->set(i, temp);
                        }
                    }
                }
            }
        }
    }
}