#include "headers/item.hpp"

namespace Lib {
    Item::Item() {
        this->ID = UNDEFINED_ID;
        this->name = "UNDEFINED";
        this->type = "UNDEFINED";
        this->basetype = "UNDEFINED";
    }

    // Implementasi Item
    Item::Item(int ID, string name, string type, string basetype) {
        this->ID = ID;
        this->name = name;
        this->type = type;
        this->basetype = basetype;
    }

    Item::Item(const Item& i) {
        this->ID = i.ID;
        this->name = i.name;
        this->type = i.type;
        this->basetype = i.basetype;
    }

    Item::~Item() {

    }

    int Item::getID() const {
        return this->ID;
    }

    string Item::getName() const {
        return this->name;
    }

    string Item::getType() const {
        return this->type;
    }

    string Item::getBType() const {
        return this->basetype;
    }

    void Item::displayInfo() const {
        cout << setw(NUMWIDTH) << this->ID << " | "
            << setw(WIDTH) << this->name << " | "
            << setw(WIDTH) << this->type << " | "
            << setw(WIDTH) << this->basetype;
    }

    int Item::getQuantity() const{ return 0; }
    int Item::getDurability() const { return 0; }
    void Item::setQuantity(int) {}
    void Item::useItem() {}

    // Implementasi bagian Non Tool Item
    NonTool::NonTool(int ID, string name, string type, string basetype, int quant)
        : Item(ID, name, type, basetype) {
        this->quantity = quant;
    }

    NonTool::NonTool(const NonTool& nt) : Item(nt) {
        this->quantity = nt.quantity;
    }

    NonTool::~NonTool() {

    }

    NonTool& NonTool::operator=(const NonTool& other) {
        this->ID = other.ID;
        this->name = other.name;
        this->type = other.type;
        this->basetype = other.basetype;
        this->quantity = other.quantity;
        return *this;
    }

    int NonTool::getQuantity() const {
        return this->quantity;
    }

    void NonTool::setQuantity(int quant) {
        this->quantity = quant;
    }

    void NonTool::addItem(int quant) {
        //quite unsure about this part
        //semua item bertipe sama mo dijadiin satu item yang sama
        //ato dikelompokin berdasarkan stack?
        //ato masalah stacking diatur di inventory?

        // sementara dicap dulu, this is friday night
        this->quantity += quant;
    }

    void NonTool::useItem(int quant) {
        //sama dengan yang diatas
        this->quantity -= quant;
    }

    void NonTool::displayInfo() const {
        Item::displayInfo();
        cout << " | QTY: " << this->quantity;
    }

    // Implementasi bagian Tool Item
    Tool::Tool(int ID, string name, string type, string basetype, int dur)
        : Item(ID, name, type, basetype) {
        this->durability = dur;
    }

    Tool::~Tool() {

    }

    Tool& Tool::operator=(const Tool& other) {
        this->ID = other.ID;
        this->name = other.name;
        this->type = other.type;
        this->basetype = other.basetype;
        this->durability = other.durability;
        return *this;
    }

    int Tool::getDurability() const {
        return this->durability;
    }

    void Tool::useItem() {
        this->durability--;
        if (this->durability == 0) {
            //quite unsure about this part yet
            cout << "Your " << this->name << " broke." << endl;
            delete this;
        }
    }

    void Tool::displayInfo() const {
        Item::displayInfo();
        cout << " | DUR: " << this->durability;
    }
}