#include "headers/inventory.hpp"

template <class T>
Inventory<T>::Inventory(){
    this->inv_buffer = new T[INV_ROWS][INV_COLS];
}

template <class T>
Inventory<T>::~Inventory(){
    delete[] this->inv_buffer;
}

template <class T>
T getItem(int x, int y){
    return this->inv_buffer[x][y];
}

template <class T>
T setItem(int x, int y, T item){
    this->inv_buffer[x][y] = item;
}

template <class T>
void Inventory<T>::display(){
    for (int i = 0; i < INV_ROWS; i++){
        for (int j = 0; j < INV_COLS; j++){
            cout << "[" << this->inv_buffer[i][j].getID() << " " << (i * INV_COLS + j) << "] ";
            if (j == INV_COLS - 1){
                cout << endl;
            }
        }
        cout << endl;
    }
}