#include <fstream>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;

class user {
    string Name;
    int Enters;

public:

    string namGet() {

        return Name;
    }
    int neGet() {

        return Enters;
    }
    void nameSet(string UsrName) {

        Name = UsrName;

    }
    void entSet(int Numb) {

        Enters = Numb;
    }

    user() {

        Name = "User";
        Enters = 0;

    }
    //raspechatka
    void print(user& user, int size);
    
    // zapis resultatov
    void record(user& user, int size);
};

//raspechatka spiska pobeditilei
void user::print(user& user, int size) {

    if (size == 1) { cout << "list is empty\n"; }

    else {

        for (int i = 0; i < size;i++) {

            cout << this[i].namGet() << '\t';
            cout << this[i].neGet() << '\n';
        }

    }
};

void user::record(user& user, int size) {

    int resTMP;
    string nameTMP;

    std::ofstream list("list");

    for (int i = 0; i < size; i++) {
        nameTMP = this[i].namGet();
        list << nameTMP << ' ';
        resTMP = this[i].neGet();
        if (i == (size - 1))list << resTMP;
        else list << resTMP << ' ';
    }

    list.close();
}



// podschet neobhodimii razmer massiva
int masVol() {
    int count = 0;
    string load;
    std::ifstream file("list");
    if (!file.is_open()) {
        cout << "List of winners is empty!\n";
        
        return 0;
    }
    else {

        std::getline(file, load);
        
        for (int i = 0; i < load.size(); i++)
        {
            if (load[i] == ' ') count++;
        }
        count++;
        count /= 2;

        return count;
    }
    file.close();

}

// sortirovka
void bublsort(user* ddd, int size) {

    int tmp, tmp1;
    string tmps, tmps1;
   for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--)
          {
                if (ddd[j - 1].neGet() > ddd[j].neGet())
                {
                    tmps = ddd[j - 1].namGet();
                    tmps1 = ddd[j].namGet();
                    ddd[j - 1].nameSet(tmps1);
                    ddd[j].nameSet(tmps);
                    tmp = ddd[j - 1].neGet();
                    tmp1 = ddd[j].neGet();
                    ddd[j - 1].entSet(tmp1);
                    ddd[j].entSet(tmp);
                    

                }
        }
    }
    
}


int main(int argc, char* argv[])
{
    int size = 0;// razmer variatsii
    
    int randNumb, inpValue, tries = 1;// dlya igri



    // sozdaem massiv dlya spiska pobiditelei
    string tmp;// vremennaia peremennai
    int x;
    int arrSize; // razmer massiva
    arrSize = masVol()+1;
    user* curArr = new user[arrSize];
    
     
    
    // zapolnyem massiv   
    std::ifstream file("list");
    
    for (int i = 0; i < (arrSize-1);i++) {

        file >> tmp;
        curArr[i].nameSet(tmp);
        file >> x;
        curArr[i].entSet(x);
    }
    
  
    // obrabotka kommand konsoli
    if (argc > 1 && argc < 4) {
        string choose{ argv[1] };
        if (choose == "-level") {
            size = atoi(argv[2]);
            if (size == 1) size = 10;
            if (size == 2) size = 50;
            if (size == 3) size = 100;
            else (cout << "wrong parametr of -level \n ");
        }
        if (choose == "-table") { curArr->print(*curArr, (arrSize)); return 0; }
        if (choose == "-max") size = atoi(argv[2]);


    }
    else { cout << "default settings are set \n"; size = 100; }


    // obrabotka dannih tekushego igroka
    cout << "please enter your Name: \n";
    cin >> tmp;

    curArr[(arrSize - 1)].nameSet(tmp);

    std::srand(std::time(nullptr));
    randNumb = rand() % size + 1;

    cout << " Enter your quess:";
    cin >> inpValue;

    // igra
    while (randNumb != inpValue) {
        
        if (inpValue > randNumb) cout << "too much \n";
        else  cout << "too little \n";
        cout << "try again:\n";
        cin >> inpValue;
        tries++;
    }

    cout << " You win!!!\n";
    cout << " Your number of tries " << tries << '\n';
    curArr[(arrSize-1)].entSet(tries);

    // zapis resultatov
    
    
    curArr->record(*curArr, (arrSize));

    // sortirovaka spiska
    bublsort(  curArr, arrSize);
    
    //vivod spiska
    cout << "Hihgscore table \n";
    curArr->print(*curArr, (arrSize));


  delete [] curArr;
}

