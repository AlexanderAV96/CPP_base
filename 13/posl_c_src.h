
#include "posl_c.h"





template<typename T>
void p_cont <T>:: pushback(T novii) {

    
   
    if(size < capacity) {
        arr[size++]=novii;
          
    }
    
    else {
        if (capacity == 0) capacity++;
        capacity *= 2;
        T* copy = arr;        
        arr = new T[capacity];
       // arr = reinterpret_cast <T*>(new char[capacity * sizeof(T)]);//videlyaem mesto dlya "capacity" elementov typa T i castuem ih k ukazatelu
        for (int i = 0; i < size;i++) {
           
            arr[i] = copy[i]; //budet oshibka exli ostavit tak - net polei -> vizivaem konstruktor
            //new(arr + i)T(copy[i]);// vizov konstruktora po zadannomu adresu

        }

        

       
        //
        //for (size_t i = 0; i < size;i++) {// vmesto delete vizivaem distructor
        //    (copy + i)->~T();

        //}
        
      //???  delete[] reinterpret_cast<int8_t*>(copy);
        
        arr[size++]=novii;
        delete[] copy;
        
    }
};


template<typename T>
void p_cont <T>::insert( T novii, size_t location) {
   
    //T novii;
    //int location = 0;
    //cout << "Inpute new digit: \n";
    //cin >> novii;
    //cout << "Inpute location: \n";
    //cin >> location;
    
    
    if (size < capacity) {
       
        size++;
        
        
       // new(arr + size)T(arr[size - 2]);//2
        
        for (size_t i = size; i > (location - 1);i--) {

            
            arr[i] = arr[i - 1];
            //arr[i]=(std::move(arr[i - 1]));
        }
        arr[location - 1]=novii;

    }
    else {
        
        if (capacity == 0) capacity++;
        capacity *= 2;

        T* copy = arr;
        arr = new T[capacity];

        //arr = reinterpret_cast <T*>(new char[capacity * sizeof(T)]);//videlyaem mesto dlya "capacity" elementov typa T i castuem ih k ukazatelu
       

        // podstanovka
        size_t i = 0, n = 0;
        for (; i < location;i++) {
            arr[i ] = copy[i];
           // new(arr + i)T(copy[i]);
        }

        arr[location - 1] = novii;
       // new(arr + location)T(novii);

        for (; i < size;i++) {
            
            arr[i + 1] = copy[i];
            //new(arr + i + 1)T(copy[i]);

        }
        

        //for (size_t i = 0; i < size;i++) {// vmesto delete vizivaem distructor
        //    (copy + i)->~T();

        //}

        //delete[] reinterpret_cast<int8_t*>(copy);

        size++;
        delete[] copy;
    }
    

};




template<typename T>
void p_cont <T>::erase(size_t location) {

    
    
    T* copy = arr;
    
    arr = new T [capacity]; // !!! v etom meste problema, esli ispolzovat if dlya umenshenia massiva to dalee novii massiv ne rabotaet
   // arr = reinterpret_cast <T*>(new char[capacity * sizeof(T)]);
    
  
   
    size_t i = 0;
    for (; i < (location-1);i++) {
       arr[i] = copy[i];
      //  new(arr + i)T(copy[i]);
    }
    i++;
    for (; i < size;i++) {
      //  new(arr + i - 1)T(copy[i]);
        arr[i-1] = std::move(copy[i]);
    }
   
    //
    //for (size_t i = 0; i < size;i++) {// vmesto delete vizivaem distructor
    //    (copy + i)->~T();

    //}

    //delete[] reinterpret_cast<int8_t*>(copy);
    size--;

   delete[] copy;
    
};



template<typename T>
void p_cont <T>::print() {
    //T n;
    for (size_t i = 0; i < size;i++) {
        /*n = this[i];*/
        cout << arr[i] << '\t';
    }
    cout << '\n';
    cout << '\n';
};

