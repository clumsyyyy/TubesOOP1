#ifndef ITEM_CPP
#define ITEM_CPP

#define MAX_STACK 64
#include <iostream>
#include <string>
using namespace std;

class Item{
    protected:
        int ID;          // item ID (e.g. 24)
        string name;     // item name (e.g. "DIAMOND_SWORD")
        string type;     // item type (TOOL/NONTOOL)
        string basetype; // basetype (oak log basetypenya log)
    public:
        Item(int, string, string, string); // user-defined constructor
        virtual ~Item(); // virtual destructor
        int getID() const;
        string getName() const;
        string getType() const;
};

class NonToolItem : public Item {
    private:
        int quantity;
    public:
        NonToolItem(int, string, string, string, int);
        ~NonToolItem();
        int getQuantity() const;
        void setQuantity(int);
        void useItem(int);
        void addItem(int);
};

class ToolItem : public Item {
    private: 
        int durability; // durability of the tool
    public:
        ToolItem(int, string, string, string);
        ~ToolItem();
        int getDurability() const;
        void useItem();
};

#endif