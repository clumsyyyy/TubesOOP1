#include "headers/item.hpp"

namespace Lib {
    /* IMPLEMENTATION FIELD FOR PARENT CLASS: Item */
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

    bool Item::isTool() {
        return this->basetype == "TOOL";
    }

    bool Item::isNonTool() {
        return this->basetype == "NONTOOL";
    }

    bool Item::isUndef() {
        return this->basetype == "UNDEFINED";
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

    /* IMPLEMENTATION FIELD FOR CHILD CLASS: NonTool */

    NonTool::NonTool(int ID, string name, string type, string basetype, int quant)
        : Item(ID, name, type, basetype) {
        this->quantity = quant;
    }

    NonTool::NonTool(const TupleItem& item, int quant) : NonTool(
        stoi(get<0>(item)),
        get<1>(item),
        get<2>(item),
        get<3>(item),
        quant
    ) {}

    NonTool::NonTool(const NonTool& nt) : Item(nt.ID, nt.name, nt.type, nt.basetype) {
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

    /* IMPLEMENTATION FIELD FOR CHILD CLASS : Tool */

    /**
     * @brief Construct a new Tool:: Tool object
     * 
     * @param ID ID of the tool
     * @param name name of the tool
     * @param durability durability of the tool
     */
    Tool::Tool(int ID, string name, int durability)
        : Item(ID, name, "TOOL", "-") {
        this->durability = durability; // Default durability = 10
    }

    Tool::Tool(const TupleItem& item, int durability) : 
    Tool(
        stoi(get<0>(item)),
        get<1>(item),
        durability
    ) {}

    Tool::Tool(const Tool& t) : Item(t.ID, t.name, t.type, t.basetype) {
        this->durability = t.durability;
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

    /**
     * @brief Decrease durability of the tool
     * 
     */
    void Tool::useItem() {
        this->durability--;
        if (this->durability == 0) {
            cout << "Your " << this->name << " broke." << endl;
            delete this;
        }
    }

    void Tool::displayInfo() const {
        Item::displayInfo();
        cout << " | DUR: " << this->durability;
    }
}