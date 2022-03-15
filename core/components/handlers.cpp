#include "headers/handlers.hpp"
#include "../globals.hpp"

void DetailsHandler(){
    string mode;
    cin >> mode;
    if (mode == "ALL"){
        inv->displayDetails();
    } else if (mode == "ITEM"){
        int i;
        cin >> i;
        inv->specify(i);
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
    if (inv->get(index).getBType() == "NONTOOL"){
        inv->discard(quant, index);
    } else {
        inv->set(index, new Item());
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
        for (int i = 0; i < CRAFT_SIZE; i++) {
            if (crftab->get(i).getName() == name) {
                crftab->get(i).setQuantity(crftab->get(i).getQuantity()-1);
            }
        
        }
        GiveChecker(name, durability);
        crf.returning();
    } else {
        throw "Recipe not found\n";    
    }
}