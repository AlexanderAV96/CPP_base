#include "pch.h"
#include "../lst.h"
#include "../lst_src.h"

TEST(list_test, push_back_non_INT_test) {

	MyList <char> test;
	test.pushback('r');

	EXPECT_EQ(test[0], 'r');
	
}
TEST(list_test, push_back_test) {

	MyList <int> test;
	test.pushback(0);

	EXPECT_EQ(test[0], 0);
	
}


TEST(list_test, push_begin_test) {
	MyList <int> test;
	test.pushfront(2);
	test.pushfront(1);
	test.pushfront(0);

	EXPECT_EQ(test[0], 0);
	
}




TEST(list_test, push_middle_list) {
	MyList <int> test;
	test.pushback(5);
	test.pushback(5);
	test.insert(22, 2);

	EXPECT_EQ(test[1], 22);
	
	EXPECT_EQ(test.getsize(), 3);
	
}


TEST(list_test, pop_end_test) {
	MyList <int> test;

	test.pushback(5);
	test.pushback(10);
	test.remove(2);

	EXPECT_EQ(test.getsize(), 1);
	
	EXPECT_EQ(test[0], 5);
	
}




TEST(list_test, pop_begin_test) {
	MyList <int> test;

	test.pushback(5);
	test.pushback(10);
	test.popfront();

	EXPECT_EQ(test.getsize(), 1);
	
	EXPECT_EQ(test[0], 10);
	
}


TEST(list_test, pop_middle_test) {
	MyList <int> test;
	test.pushback(2);
	test.pushback(1);
	test.pushback(0);
	test.remove(2);

	EXPECT_EQ(test.getsize(), 2);
	
	EXPECT_EQ(test[1], 0);
	
}

TEST(list_test, get_size_test) {
	MyList <int> test;
	test.pushback(2);
	test.pushback(1);
	test.pushback(0);


	EXPECT_EQ(test.getsize(), 3);
	
}
TEST(list_test, get_data_test) {
	MyList <int> test;
	test.pushback(2);
	test.pushback(1);
	test.pushback(0);



	EXPECT_EQ(test[1], 1);
	
}

TEST(list_test, copy_const__test) {
	MyList <int> testL;
	testL.pushback(10);
	testL.pushback(20);
	testL.pushback(30);

	MyList <int> testL2;
	testL2.pushback(40);
	testL2.pushback(50);

	testL2 = testL;


	EXPECT_EQ(testL[0], testL[0]);
	
	EXPECT_EQ(testL[1], testL[1]);
	
	EXPECT_EQ(testL[2], testL[2]);
	

	
}

TEST(list_test, clear_dyn_mem_test) {

	static int delet_count = 1;// MyStruct a - budet udelen posle zavershenia programmi

	struct MyStruct
	{

		~MyStruct() {

			delet_count--;
		}

		MyStruct() {

			delet_count++;
		}
	};

	MyStruct a;
	MyList <MyStruct> testL;
	testL.pushback(a);
	testL.popfront();

	EXPECT_EQ(delet_count, 0);
	


}