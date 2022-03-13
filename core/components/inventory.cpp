#include "headers/inventory.hpp"

Inventory::Inventory(){
    this->inv_buffer = new Item*[INV_ROWS * INV_COLS]; 
    for (int i = 0; i < INV_ROWS * INV_COLS; i++){
        this->inv_buffer[i] = new Item();
    }
}

Inventory::~Inventory(){
    delete[] this->inv_buffer;
}

Item Inventory::get(int i, int j){
    return *(this->inv_buffer[i*INV_COLS + j]) ;
}

void Inventory::set(int i, int j, Item* item){
    (this->inv_buffer[i * INV_COLS + j]) = item;
};

void Inventory::displayMenu(){
    for (int i = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            cout << "[(" << i << ", " << j << ") " 
            << (this->inv_buffer[i * INV_COLS + j])->getID() << " "
            << (this->inv_buffer[i * INV_COLS + j])->getQuantity() << " "
            << (this->inv_buffer[i * INV_COLS + j])->getDurability() << "] ";
            if (j == INV_COLS - 1){
                cout << endl;
            }
        }
        cout << endl;
    }
};

void Inventory::displayDetails(){
    cout <<  "  Slot" << " | " 
    << setw(NUMWIDTH) << "ID" << " | " 
    << setw(WIDTH) << "Name" << " | " 
    << setw(WIDTH) << "Type" << " | " 
    << setw(WIDTH) << "Base Type" << endl;
    for (int i = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            cout << "(" << i << ", " << j << ") | ";
            this->specify(i, j);
            cout << endl;
        }
    }
};

void Inventory::specify(int i, int j){
    (this->inv_buffer[i * INV_COLS + j])->displayInfo();
}

void Inventory::addNonTool(NonTool* item){
    for (int i = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            // base case if no such item exists in inventory
            if (this->get(i, j).getID() == UNDEFINED_ID){
                if (item->getQuantity() <= MAX_STACK){
                    this->set(i ,j, item);
                    cout << "set item " << item->getID() << " to (" << i << ", " << j << ")" << endl;
                    return;
                } else {
                    NonTool* temp = new NonTool(*item);
                    temp->setQuantity(MAX_STACK);
                    this->set(i ,j, temp);
                    cout << "set item " << temp->getID() << " to (" << i << ", " << j << ")" << endl;
                    cout << item->getQuantity()<< " stacks left" << endl;
                    item->setQuantity(item->getQuantity() - MAX_STACK);
                    continue;
                }
            // case 1: other item exists (stackable)
            } else if (this->get(i, j).getID() == item->getID()){
                // if current slot less than max stack, increase quantity
                if (this->get(i, j).getQuantity() + item->getQuantity() <= MAX_STACK){
                    this->get(i, j).setQuantity(this->get(i, j).getQuantity() + item->getQuantity());
                    return;
                } else {
                    if (j == INV_COLS - 1){
                        if (i == INV_ROWS - 1){
                            cout << "Inventory is full" << endl;
                            return;
                        } else {
                            this->set(i + 1, 0, item);
                            return;
                        }
                    } else {
                        this->set(i, j + 1, item);
                        return;
                    }
                }
                return;
            }
        }
    }
}

void Inventory::addTool(Tool* item){
     for (int i = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            // base case if no such item exists in inventory
            if (this->get(i, j).getID() == UNDEFINED_ID){
                this->set(i ,j, item);
                cout << "set item " << item->getID() << " to (" << i << ", " << j << ")" << endl;
                return;
            }
        }
     }
}

void Inventory::discard(int quant, int slot){
    if (this->inv_buffer[slot]->getQuantity() - quant >= 0){
        this->inv_buffer[slot]->setQuantity(this->inv_buffer[slot]->getQuantity() - quant);
    } else {
        cout << "Not enough items in slot" << endl;
    }
}