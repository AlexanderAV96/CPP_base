#pragma once
#include <vector>
#include <iostream>
using std::cin;
using std::cout;

template<typename T>
class p_cont {

    T *arr;
    int size = 0;
    int capacity = 0;
    
public:
    // p_cont& operator [](int i) {  };
    T& operator [](int place);
   
    const T& operator [](int place) const{
        return arr[place];
    };

    void pushback(T novii)  ;//+

    void insert(T novii,int location ) ;//+

    //void insert_no_ar();

    //void move_LtoF(p_cont*& arr, int& elements) {// ne nujen


    //    //test move

    //    arr[0].set_x(std::move(arr[elements - 1].get_x()));

    //}


    void erase(int loation) ;//+

    int get_capacity() const { return capacity; };//+

    int get_size() const { return size; };//+

    void set_capacity(int capacity) { this->capacity = capacity; };//+

    void set_size(int size) { this->size = size; };//+

    p_cont() {};
    
    
    
    
    p_cont(int temp) {
    
        this->capacity = temp;
        this->size = temp;
        arr = new T [temp];


        for (int i = 0; i < size; i++) {
           arr[i]=i;
        }

     };
    ~p_cont() {
    
        delete[] arr;
    };

    T get_x() { return arr; };

    //void set_x(T z) { arr[] = z; };

    void print() ;//+


    p_cont(p_cont& other) {
        if (this != &other) {
            delete[] arr;
            arr = new T[other.capacitye];
            for (int i = 0; i < other.size; ++i) arr[i] = other.arr[i];
            size = other.size;
            capacity = other.capacity;
        }
    }
};
