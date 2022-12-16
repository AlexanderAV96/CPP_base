#include "posl_c.h"
#include "lst.h"
#include "posl_c_src.h"
#include "lst_src.h"

#include <iostream>




int main()
{
	
	size_t new_size = 10;
	std::cout << "List \n";

	// list
	MyList <int> testL;
	for (int i = 0; i < new_size; i++) {
		testL.pushback(i);
	}
	MyList <int> testL2;

	
		
	
	testL.print();
	//4
	std::cout << testL.getsize() << '\n';
	//5
	testL.remove(3);
	testL.remove((5-1));
	testL.remove((7-2));
	//6
	testL.print();
	//7
	testL.pushfront(10);
	//8
	testL.print();
	//9
	testL.insert(20, (testL.getsize() / 2 + 1));
	//10
	testL.print();
	//11
	testL.pushback(30);
	//12
	testL.print();

	//arr
	
	std::cout << "Array \n";

	p_cont <int> testV(10);

	testV.print();
		
	//4
	std::cout << testV.get_size() << '\n';
	//5
	testV.erase(3);
	testV.erase((5-1));
	testV.erase((7-2));
	//6
	testV.print();
	//7
	testV.insert(10,1);
	//8
	testV.print();
	//9
	testV.insert(20, (testV.get_size() / 2 + 1));
	//10
	testV.print();
	//11
	testV.pushback(30);
	//12
	testV.print();
	


	



}

 