#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#define INV_COLS 9
#define INV_ROWS 3

template <class T>
class Inventory{
    private:
        T* inv_buffer;
    public:
        //user-defined: create empty inventory
        Inventory();
        ~Inventory();
        T getItem(int x, int y);
        T setItem(int x, int y, T item);
        void display();
};
#endif