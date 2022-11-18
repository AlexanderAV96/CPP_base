#include "lst.h"
#include "lst_src.cpp"






int main()
{

	MyList <int> test;
	int number = 1, location = 1;

	int size_p = 10;    // razmer massiva dlya testa
	// zapolnyem
	for (int i = 0; i < size_p;i++) { test.pushback(i); }





	char input = 'k'; //dlya switch

	while (input != 'q') {

		std::cout << "Please input number of action or input 'q' to exit \n";
		cout << "1. Add new digit \n";
		cout << "2. Add a new digit to the specific location in the array \n";
		cout << "3. Remove element from the array  \n";

		cout << "4. Print the array \n";
		cout << "5. Print size of the array \n";
		cout << '\n';
		cout << '\n';

		std::cin >> input;



		switch (input)
		{
		case '1': {
			cout << "Enter figure:";
			std::cin >> number;
			test.pushback(number);
			break;}

		case '2': {

			cout << "Enter figure:";
			std::cin >> number;
			cout << "Enter location:";
			std::cin >> location;


			test.insert(number, location);
			break;}

		case '3': {


			cout << "Enter location of removable number:";
			std::cin >> location;


			test.remove(location);
			break;	}


		case '4':

		{


			test.print(test);
			break; }

		case '5':

			cout << test.getsize() << '\n';

			break;

		default:
			return 0;
		}

	}




}
