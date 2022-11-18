
#include "Header.h"
#include "Source.cpp"






int main()
{
    int size_p = 10;    // razmer massiva
    int elements = 10; // dlya ucheta poslednei znyatoi pozitsii
    p_cont<int>* some = new p_cont<int>[size_p];

    //zapolnyaem konteiner
    for (int i = 0; i < elements; i++) {
        some[i].set_x(i);
    }
    


    char input = 'k'; //dlya switch

    while (input != 'q') {

        cout << "Please input number of action or input 'q' to exit \n";
        cout << "1. Add new digit \n";// !!!!!!!!!
        cout << "2. Add a new digit to the specific location in the array \n";
        cout << "3. Remove element from the array  \n";
      //  cout << "6. Move last element to beging \n";
        cout << "4. Print the array \n";//!!!!!!!!!!!!!!!!!
        cout << "5. Print size of the array \n";//!!!!!!!!!!!!!!!!!
        cout << '\n';
        cout << '\n';

        cin >> input;
        


        switch (input)
        {
        case '1':// esli elemetov = razmer => true to pushback
            if (elements == size_p) {
                some->pushback(size_p, some, elements);
                break;
            }
            int novii;
            cout << "Inpute new digit: \n";
            cin >> novii;
            some[elements].set_x(novii);
            elements++;
            break;

        case '2':
            
            if (elements == size_p) {
                some->insert(size_p, some, elements);
                break;
            }
            else some->insert_no_ar( some, elements);

            break;
        case '3':

            some->erase(size_p, some, elements);


            break;
       
        case '6':

            //some->move_LtoF(some, elements);

            break;
       
        case '4':

            some->print(some,elements);

            break;
        
        case '5':

            some->get_size(size_p);

            break;
        default:
            return 0;
        }
        

    }


    delete[] some;
    return 0;
}


