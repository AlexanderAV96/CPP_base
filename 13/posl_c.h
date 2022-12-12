#pragma once
#include <vector>
#include <iostream>
using std::cin;
using std::cout;

static int posl_count = 0;

template<typename T>
class p_cont {

    T *arr;
    size_t size = 0;
    size_t capacity = 0;
    
public:
    // p_cont& operator [](int i) {  };
    T& operator [](size_t place) {   return arr[place];  };
   
    const T& operator [](size_t place) const{  return arr[place];    };

    void pushback(T novii)  ;//+

    void insert(T novii, size_t location ) ;//+

   
    void erase(size_t location) ;//+

    int get_capacity() const { return capacity; };//+

    int get_size() const { return size; };//+

    void set_capacity(size_t capacity) { this->capacity = capacity; };//+

    void set_size(size_t size) { this->size = size; };//+

    p_cont() {  };
    
    
    
    
    p_cont(size_t new_size){
    
        this->capacity = new_size;
        this->size = new_size;
        arr = new T[new_size];


        for (int i = 0; i < size; i++) {
           arr[i]=i;
        }
        posl_count++;
     };
    ~p_cont() {
      
        // delete[] reinterpret_cast<int8_t*>(arr);
        delete[] arr;
        posl_count--;
    };

    T get_x() { return arr; };

    //void set_x(T z) { arr[] = z; };

    void print() ;//+


    p_cont(p_cont& other) {
       /* if (this != &other) {
            delete[] arr;
            arr = new T[other.capacitye];
            for (int i = 0; i < other.size; ++i) arr[i] = other.arr[i];
            size = other.size;
            capacity = other.capacity;
        }*/
        this->size = other.size;
        this->arr = new T[other.size];
        for (size_t i = 0; i < other.size;i++) {
            this->arr[i] = other.arr[i];
        }
        posl_count++;
    }

    p_cont& operator =(p_cont& other) {
        this->size = other.size;
        this->arr = new T[other.size];
        for (size_t i = 0; i < other.size;i++) {
            this->arr[i] = other.arr[i];
        }
        return *this;
    };
};
