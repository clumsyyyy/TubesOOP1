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
        int min = 0;        
        string name;
        Crafting crf;
        crf.recipe(tup);
        name = crf.getName();
        sum = crf.getSum();
        if (sum > 0){
            GiveChecker(name, sum);
            cout << "crafted " << sum << " " << name << endl;
            crf.returning();
            return; 
        }
    }
    Crafting crf;
    int durability = crf.tools(); 
    int sum = crf.getSum();
    string name = crf.getName();

    if (sum == 2) {
        for (int i = 0; i < CRAFT_COLS; i++) {
            for (int j = 0; j < CRAFT_ROWS; j++) {
                if (crftab->get(i ,j).getName() == name) {
                    crftab->get(i, j).setQuantity(crftab->get(i,j).getQuantity()-1);
                }
            }
        }
        GiveChecker(name, durability);
        crf.returning();
    } else {
        throw "Recipe not found\n";    
    }
}