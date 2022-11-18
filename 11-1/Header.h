#pragma once

#include <iostream>
using std::cin;
using std::cout;

template<typename T>
class p_cont {

    T x;


public:
    // p_cont& operator [](int i) {  };


    void pushback(int& size, p_cont*& arr, int& elements)  ;

    void insert(int& size, p_cont*& arr, int& elements) ;

    void insert_no_ar(p_cont*& arr, int& elements);

    //void move_LtoF(p_cont*& arr, int& elements) {// ne nujen


    //    //test move

    //    arr[0].set_x(std::move(arr[elements - 1].get_x()));

    //}


    void erase(int& size, p_cont*& arr, int& elements) ;

    void get_size(int size_p) ;

    T get_x() { return x; };

    void set_x(T z) { x = z; };

    void print(p_cont* arr, int elements) ;
};
