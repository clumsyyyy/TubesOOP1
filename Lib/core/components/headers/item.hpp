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
        string basetype; // basetype (PLANK/LOG/STONE/...)
    public:
        /**
         * @brief Construct a new Item object based on 
         * user-defined values
        */
        Item(int, string, string, string); // user-defined constructor

        /**
         * @brief Copy constructor
         * 
         * @param i 
         */
        Item(const Item& i); // copy constructor

        /**
         * @brief copies an item with inheritance
         * 
         * @return Item* 
         */
        Item* copy(); 

        // Getters / Setters
        /**
         * @brief gets the ID of the item
         * 
         * @return int 
         */
        int getID() const;

        /**
         * @brief Get the name of the item
         * 
         * @return string 
         */
        string getName() const;

        /**
         * @brief Get the item type
         * 
         * @return string 
         */
        string getType() const;

        /**
         * @brief Get the basetype of the item
         * 
         * @return string 
         */
        string getBType() const;

        // Validators 
        bool isTool();
        bool isNonTool();
        virtual void displayInfo() const;
    };
    class NonTool : public Item {
    private:
        int quantity;
    public:
        /**
         * @brief Construct a new Non Tool object based on
         * user-defined values
         */
        NonTool(int, string, string, string, int);

        /**
         * @brief Construct a new Non Tool object based
         * on the item tuple
         */
        NonTool(const TupleItem&, int);
        
        /**
         * @brief Copy constructor
         * @param nt 
         */
        NonTool(const NonTool& nt);

        /**
         * @brief Typecasts an item into a non-tool
         * 
         * @return NonTool& 
         */
        static NonTool& FromItem(const Item*);

        /**
         * @brief Overload the = operator to set
         * an item variable to existing item
         * (copy constructor)
         * @param other another item
         * @return NonTool& 
         */
        NonTool& operator=(const NonTool& other);

        /**
         * @brief Get the quantity of a non-tool item
         * 
         * @return int 
         */
        int getQuantity() const;

        /**
         * @brief Set the quantity of a non-tool item
         * 
         */
        void setQuantity(int);

        /**
         * @brief Displays the information of the item
         * 
         */
        void displayInfo() const;
    };

    class Tool : public Item {
    private:
        int durability; // durability of the tool
    public:

        /**
         * @brief Construct a new Tool object based on
         * user-defined values and predetermined durability
         */
        Tool(int, string, int);

        /**
         * @brief Construct a new Tool object based on
         * user-defined values and default durability (10)
         */
        Tool(int, string);

        /**
         * @brief Construct a new Tool object based on
         * item tuple
         */
        Tool(const TupleItem&, int);
        Tool(const TupleItem&);

        /**
         * @brief Copy constructor for the tool
         * 
         */
        Tool(const Tool&);

        /**
         * @brief Typecasts an item into a tool
         * 
         * @return Tool& 
         */
        static Tool& FromItem(const Item*);

        /**
         * @brief Overload the = operator to set
         * an item variable to existing item
         * (copy constructor)
         * @param other 
         * @return Tool& 
         */
        Tool& operator=(const Tool& other);

        /**
         * @brief Get the durability value of a tool item
         * 
         * @return int 
         */
        int getDurability() const;

        
        /**
         * @brief Set the durability value of a tool item
         * 
         * @return int 
         */
        void setDurability(int);

        /**
         * @brief Use the tool item and reduce the 
         * durability value
         */
        void useItem();

        /**
         * @brief Displays info of the item
         * 
         */
        void displayInfo() const;
    };
}

#endif