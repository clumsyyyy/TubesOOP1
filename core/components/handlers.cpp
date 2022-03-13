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
    }
}

void GiveHandler() {
    string name;
    int quant;
    cin >> name >> quant;
    for(tuple tup : itemConfig){
        if(get<1>(tup) == name && get<3>(tup) == "NONTOOL"){
            NonTool* NT = new NonTool(stoi(get<0>(tup)), get<1>(tup), get<2>(tup), get<3>(tup), quant);
            inv->add(NT);
            break;
        } else {
            //THROW EXCEPTION HERE
        }
    }
}