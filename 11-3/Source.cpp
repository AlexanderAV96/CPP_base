#pragma once
#include "Header.h"

template<typename T>
T& p_cont<T>::operator [](int place) {

    //int i = 0;
    //
    //while (i < capacity) { // do kontsa

    //    if (i == place)
    //    {
            return arr[place]; // esli sovpadaet to vozvrashaem dannie
   /*     }
        i++;
    }*/
}

//template<typename T>
//const T& p_cont<T>::operator [](int place) const {
//
//    
//        
//            return arr[place]; // esli sovpadaet to vozvrashaem dannie
//        
//       
//    
//}


template<typename T>
void p_cont <T>:: pushback(T novii) {

    /*T novii;
    cout << "Inpute new digit: \n";
    cin >> novii;*/

   
    if(size < capacity) {
        arr[size++]=novii;
        /*this->size = size + 1;*/
    
    }
    
    else {
        
        capacity *= 2;
        T* copy = arr;        
        arr = new T[capacity];

        for (int i = 0; i < size;i++) {
           /* int n = 0;
            n = this[i].get_x();
            copy[i].set_x(n);*/
            arr[i] = std::move(copy[i]);

        }

        //delete[] this;

        delete [] copy;
        
        arr[size++]=novii;
       /* size +=1;*/
        
    }
};


template<typename T>
void p_cont <T>::insert( T novii, int location) {
   
    //T novii;
    //int location = 0;
    //cout << "Inpute new digit: \n";
    //cin >> novii;
    //cout << "Inpute location: \n";
    //cin >> location;
    
    
    if (size < capacity) {
       
        size++;
        
        for (int i = size; i > (location - 1);i--) {

            arr[i]=(std::move(arr[i - 1]));
        }
        arr[location - 1]=novii;

    }
    else {
        capacity *= 2;

        T* copy = arr;
        arr = new T[capacity];

        /*set_size(get_size() + 1);*/
       

        // podstanovka
        int i = 0, n = 0;
        for (; i < location;i++) {
            /* n = this[i].get_x();
             copy[i].set_x(n);*/
            arr[i] = copy[i];
        }

        arr[location - 1] = novii;

        for (; i < size;i++) {
            /* n = this[i].get_x();
             copy[i].set_x(n);*/
            arr[i + 1] = copy[i];

        }
        size++;

        delete[] copy;
    }
    /*this = copy;*/
    /*set_capacity(get_capacity() * 2);*/

};



//template<typename T>
//void p_cont <T>::insert_no_ar() {
//    T novii;
//    int location = 0;
//    cout << "Inpute new digit: \n";
//    cin >> novii;
//    cout << "Inpute location: \n";
//    cin >> location;
//
//    //test move
//
//    for (int i = size; i > (location - 1);i--) {
//
//        arr.set_x(std::move(this[i - 1].get_x()));
//    }
//    this[location - 1].set_x(novii);
//
//    set_size(get_size() + 1);

//}
template<typename T>
void p_cont <T>::erase(int location) {

    // umenshaem massiv esli bolshoi --- ne rabotaet
    
    T* copy = arr;
    
    arr = new T [capacity]; // !!! v etom meste problema, esli ispolzovat if dlya umenshenia massiva to dalee novii massiv ne rabotaet

    /*int location = 0;
    cout << "Inpute location of the removable digit : \n";
    cin >> location;*/
  
   /* T n;*/
    int i = 0;
    for (; i < (location-1);i++) {
        arr[i] = copy[i];
    }
    i++;
    for (; i < size;i++) {
       
        arr[i-1] = std::move(copy[i]);
    }
    size--;
    
    delete[] copy;
    /*this = copy;*/
};



template<typename T>
void p_cont <T>::print() {
    //T n;
    for (int i = 0; i < size;i++) {
        /*n = this[i];*/
        cout << arr[i] << '\t';
    }
    cout << '\n';
    cout << '\n';
};

