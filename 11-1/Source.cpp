#pragma once
#include "Header.h"



template<typename T>
void p_cont <T>:: pushback(int& size, p_cont*& arr, int& elements) {

    p_cont <T>* copy = new p_cont <T>[(size * 2)];

    for (int i = 0; i < elements;i++) {
        int n = 0;
        n = arr[i].get_x();
        copy[i].set_x(n);
    }

    delete[] arr;

    arr = copy;
    T novii;
    cout << "Inpute new digit: \n";
    cin >> novii;
    arr[size].set_x(novii);

    elements++;
    size *= 2;

};
template<typename T>
void p_cont <T>::insert(int& size, p_cont*& arr, int& elements) {
    p_cont <T>* copy = new p_cont <T>[(size * 2)];
    elements++;
    T novii;
    int location = 0;
    cout << "Inpute new digit: \n";
    cin >> novii;
    cout << "Inpute location: \n";
    cin >> location;

    // podstanovka
    int i = 0, n = 0;
    for (; i < location;i++) {
        n = arr[i].get_x();
        copy[i].set_x(n);
    }

    copy[location - 1].set_x(novii);

    for (; i < elements;i++) {
        n = arr[i].get_x();
        copy[i].set_x(n);
    }


    delete[] arr;
    arr = copy;
    size *= 2;

};
template<typename T>
void p_cont <T>::insert_no_ar(p_cont*& arr, int& elements) {
    T novii;
    int location = 0;
    cout << "Inpute new digit: \n";
    cin >> novii;
    cout << "Inpute location: \n";
    cin >> location;

    //test move

    for (int i = elements; i > (location-1);i--) {

        arr[i].set_x(std::move(arr[i - 1].get_x()));
    }
    arr[location - 1].set_x(novii);

    elements++;

}
template<typename T>
void p_cont <T>::erase(int& size, p_cont*& arr, int& elements) {

    // umenshaem massiv esli bolshoi --- ne rabotaet
    p_cont <T>* copy = new p_cont <T>[(size)]; // !!! v etom meste problema, esli ispolzovat if dlya umenshenia massiva to dalee novii massiv ne rabotaet


    int location = 0;
    cout << "Inpute location of the removable digit : \n";
    cin >> location;
    T n;
    int i = 0;
    for (; i < (location - 1);i++) {
        n = arr[i].get_x();
        copy[i].set_x(n);
    }
    i++;
    for (; i < elements;i++) {
        n = arr[i].get_x();
        copy[i - 1].set_x(n);
    }

    elements--;
    delete[] arr;
    arr = copy;
};

template<typename T>
void p_cont <T>::get_size(int size_p) {

    cout << size_p << '\n';

};

template<typename T>
void p_cont <T>::print(p_cont* arr, int elements) {

    for (int i = 0; i < elements;i++) {
        cout << arr[i].get_x() << '\t';
    }
    cout << '\n';
    cout << '\n';
};