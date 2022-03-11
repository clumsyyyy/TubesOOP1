#include "headers/item.hpp"

// Implementasi Item
Item::Item(int ID, string name, string type, string basetype) {
    this->ID = ID;
    this->name = name;
    this->type = type;
    this->basetype = basetype;
}

Item::~Item(){
    
}

int Item::getID() const{
    return this->ID;
}

string Item::getName() const{
    return this->name;
}

string Item::getType() const{
    return this->type;
}

// Implementasi bagian Non Tool Item
NonToolItem::NonToolItem(int ID, string name, string type, string basetype, int quant) 
: Item(ID, name, type, basetype){
    this->quantity = quant;
}

NonToolItem::~NonToolItem(){

}

int NonToolItem::getQuantity() const{
    return this->quantity;
}

void NonToolItem::setQuantity(int quant){
    this->quantity = quant;
}

void NonToolItem::addItem(int quant){
    //quite unsure about this part
    //semua item bertipe sama mo dijadiin satu item yang sama
    //ato dikelompokin berdasarkan stack?
    //ato masalah stacking diatur di inventory?

    // sementara dicap dulu, this is friday night
    this->quantity += quant;
}

void NonToolItem::useItem(int quant){
    //sama dengan yang diatas
    this->quantity -= quant;
}



// Implementasi bagian Tool Item
ToolItem::ToolItem(int ID, string name, string type, string basetype) 
: Item(ID, name, type, basetype) {
    this->durability = 10;
}

ToolItem::~ToolItem(){
    
}

int ToolItem::getDurability() const{
    return this->durability;
}

void ToolItem::useItem(){
    this->durability--;
    if (this->durability == 0){
        //quite unsure about this part yet
        cout << "Your " << this->name << " broke." << endl;
        delete this;
    }
}


