#include "headers/handlers.hpp"
#include "../globals.hpp"

void DetailsHandler(){
    string mode;
    cin >> mode;
    if (mode == "ALL"){
        inv->displayDetails();
    } else if (mode == "ITEM"){
        int i, j;
        cin >> i >> j;
        inv->specify(i, j);
        cout << endl;
    }
}

void GiveHandler() {
    string name;
    int temp;
    cin >> name >> temp;
    GiveChecker(name, temp);

}

void GiveChecker(string name, int temp) {
    for(tuple tup : itemConfig) {
        if(get<1>(tup) == name) {
            if (get<3>(tup) == "NONTOOL"){
                NonTool* NT = new NonTool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                inv->addNonTool(NT);
                break;
            } else {
                Tool* T = new Tool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), temp);
                inv->addTool(T);
                break;
            }
        } else {
            //throw exception here
        }
    }
}

void DiscardHandler(){
    string slot;
    int quant;
    cin >> slot >> quant;
    int index = stoi(slot.substr(1, slot.length() - 1));
    int i = index % INV_ROWS;
    int j = index / INV_ROWS;
    string name = inv->get(i, j).getName();
    for (tuple tup: itemConfig){
        if (get<1>(tup) == name){
            if (get<3>(tup) == "NONTOOL"){
                // if not a tool, discard
                inv->discard(quant, index);
                break;
            } else {
                // if a tool, set to undefined
                inv->set(i, j, new Item());
                break;
            }
        }
    }
}

void CraftingHandler() {
    for (tuple tup: recipeConfig) {
        int sum = 0;
        string name, temp;
        switch (get<0>(tup)) {
        case TYPE3:
            int min = crftab->get(0,0).getQuantity();
            // Check recipe
            for (int i = 0; i < TYPE3; i++) {
                for (int j = 0; j < TYPE3; j++) {
                    if (crftab->get(i, j).getName() != get<1>(tup)[i*3+j]) {
                        min = 0;
                        break;
                    }
                    if (crftab->get(i,j).getQuantity() < min) {
                        min = crftab->get(i,j).getQuantity();
                    }
                }
                if (min == 0) {
                    break;
                }
            }
            if (min > 0) {
                name = get<1>(get<2>(tup));
                sum += get<0>(get<2>(tup))*min;
                // kurangin dari inventory
            }
            // Check recipe (reflection y)
            for (int i = 0; i < CRAFT_ROWS; i++) {
                for (int j = CRAFT_COLS-1; j >= 0; j--) {
                    if (crftab->get(i, j).getName() != get<1>(tup)[i*3+j]) {
                        min = 0;
                        break;
                    }
                    if (crftab->get(i,j).getQuantity() < min) {
                        min = crftab->get(i,j).getQuantity();
                    }
                }
                if (min == 0) {
                    break;
                }
            }
            if (min > 0) {
                name = get<1>(get<2>(tup));
                sum += get<0>(get<2>(tup))*min;
                // kurangin dari inventory            
            }
            if (sum > 0){
                GiveChecker(name, sum);
                cout << "crafted " << sum << " " << name << endl;
                // balikin ke inventory
                return; 
            }
        case TYPE2:
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int min = crftab->get(i,j).getQuantity();
                    // Check recipe
                    for (int k = i, n = 0; k < 2 + i && n < 2; k++, n++) {
                        for (int l = j, m = 0; l < 2 + j && m < 2; l++, m++) {
                            if (crftab->get(k, l).getName() != get<1>(tup)[n*2+m]) {
                                min = 0;
                                break;
                            }
                            if (crftab->get(i,j).getQuantity() < min) {
                                min = crftab->get(i,j).getQuantity();
                            }
                        }
                        if (min == 0) {
                            break;
                        }
                    }
                    if (min > 0) {
                        name = get<1>(get<2>(tup));
                        sum += get<0>(get<2>(tup))*min;
                        // kurangin dari inventory 
                    }
                    // Check recipe (reflection y)
                    for (int k = i, n = 0; k < 2 + i && n < 2; k++, n++) {
                        for (int l = 1+j, m = 1; l >= j && m >= 0; l--, m--) {
                            if (crftab->get(k, l).getName() != get<1>(tup)[n*2+m]) {
                                min = 0;
                                break;
                            }
                            if (crftab->get(i,j).getQuantity() < min) {
                                min = crftab->get(i,j).getQuantity();
                            }
                        }
                        if (min == 0) {
                            break;
                        }
                    } 
                    if (min > 0) {
                        name = get<1>(get<2>(tup));
                        sum += get<0>(get<2>(tup))*min;
                        // kurangin dari inventory 
                    } 
                }
            }
            if (sum > 0){
                GiveChecker(name, sum);
                cout << "crafted " << sum << " " << name << endl;
                // balikin ke inventory
                return; 
            }
        case TYPE1:
            // Check Recipe
            for (int i = 0; i < CRAFT_ROWS; i++) {
                for (int j = 0; j < CRAFT_COLS; j++) {
                    if (crftab->get(i, j).getName() == get<1>(tup)[0]) {
                        if (crftab->get(i, j).getQuantity() > 0) {
                            name = get<1>(get<2>(tup));
                            sum += get<0>(get<2>(tup))*crftab->get(i,j).getQuantity();
                            crftab->set(i,j,new Item());
                        }
                    }
                }
            }
            if (sum > 0){
                GiveChecker(name, sum);
                cout << "crafted " << sum << " " << name << endl;
                // balikin ke inventory
                return; 
            }
        }
    }
    int sum = 0, durability = 0;
    string name; 
    for (int i = 0; i < TYPE3; i++) {
        for (int j = 0; j < TYPE3; j++) {
            if (crftab->get(i, j).getType() != "NONTOOL") {
                break;
            } else if (crftab->get(i, j).getType() != "TOOL") {
                if (sum > 0 && name != crftab->get(i, j).getName()) {
                    break;
                }
                sum++;
                name = crftab->get(i, j).getName();
                durability += crftab->get(i, j).getDurability();
                if (sum > 2) {
                    break;
                }
            }
        }
    }
    if (sum == 2) {
        // kurangi
        GiveChecker(name, durability);
        // balikin inventory
    }
    
}