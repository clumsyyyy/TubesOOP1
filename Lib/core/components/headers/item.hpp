#ifndef ITEM_CPP
#define ITEM_CPP

#include "vars.hpp"
#include <iostream>
#include <iomanip>
#include <string>
namespace Lib {
    using namespace std;

    class Item {
    protected:
        int ID;          // item ID (e.g. 24)
        string name;     // item name (e.g. "DIAMOND_SWORD")
        string type;     // item type (TOOL/NONTOOL)
        string basetype; // basetype (oak log basetypenya log)
    public:
        Item(); //default constructor
        Item(int, string, string, string); // user-defined constructor
        Item(const Item& i); // copy constructor
        virtual ~Item(); // virtual destructor
        int getID() const;
        string getName() const;
        string getType() const;
        string getBType() const;
        bool isTool();
        bool isNonTool();
        bool isUndef();
        virtual void displayInfo() const;
        virtual int getQuantity() const;
        virtual int getDurability() const;
        virtual void setQuantity(int);
        virtual void setDurability(int);
        virtual void useItem();
    };
    class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool(int, string, string, string, int);
        NonTool(const TupleItem&, int);
        NonTool(const NonTool& nt);
        ~NonTool();
        NonTool& operator=(const NonTool& other);
        int getQuantity() const;
        void setQuantity(int);
        void displayInfo() const;
    };

    class Tool : public Item {
    private:
        int durability; // durability of the tool
    public:
        Tool(int, string, int);
        Tool(const TupleItem&, int);
        Tool(const Tool&);
        ~Tool();
        Tool& operator=(const Tool& other);
        int getDurability() const;
        void setDurability(int);
        void useItem();
        void displayInfo() const;
    };
}

#endif