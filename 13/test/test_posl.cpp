#include "pch.h"
#include "../posl_c.h"
#include "../posl_c_src.h"

TEST(posl_test, push_back_non_INT_test) {

	size_t size = 10;
	p_cont <char> testV(size);
	testV.pushback('r');

	EXPECT_EQ(testV[(testV.get_size()-1)], 'r');
	
	
}
TEST(posl_test, push_begin_test) {
	p_cont <int> testV(10);
	testV.pushback(10);
	testV.pushback(20);
	testV.pushback(30);
	testV.insert(40, 1);
	


	EXPECT_EQ(testV[0], 40);
	

	
}


TEST(posl_test, push_middle_list) {
	size_t size = 10;
	p_cont <int> testV(size);
	testV.pushback(10);
	testV.pushback(20);
	testV.insert(40,(testV.get_size()/2+1));

	EXPECT_EQ(testV[6], 40);
	
	EXPECT_EQ(testV.get_size(), 13);
	

	

}


TEST(posl_test, pop_end_test) {
	size_t size = 10;
	p_cont <int> testV(size);

	testV.pushback(10);
	testV.pushback(20);
	testV.erase(12);

	EXPECT_EQ(testV.get_size(), 11);
	
	EXPECT_EQ(testV[10], 10);
	

	
}




TEST(posl_test, pop_begin_test) {
	size_t size = 10;
	p_cont <int> testV(size);

	testV.pushback(10);
	testV.pushback(20);
	testV.insert(22, 2);
	testV.erase(1);

	EXPECT_EQ(testV.get_size(), 12);
	
	EXPECT_EQ(testV[0], 22);
	

	
}


TEST(posl_test, pop_middle_test) {
	size_t size = 10;
	p_cont <int> testV(size);
	testV.pushback(10);
	testV.pushback(20);
	testV.pushback(30);
	testV.erase(12);

	EXPECT_EQ(testV.get_size(), 12);
	
	EXPECT_EQ(testV[11], 30);
	

	
}

TEST(posl_test, get_size_test) {
	size_t size = 10;
	p_cont <int> testV(size);
	testV.pushback(10);
	testV.pushback(20);
	testV.pushback(30);


	EXPECT_EQ(testV.get_size(), 13);
	

	
}

TEST(posl_test, get_data_test) {
	size_t size = 10;
	p_cont <int> testV(size);
	testV.pushback(10);
	testV.pushback(20);
	testV.pushback(30);



	EXPECT_EQ(testV[11], 20);
	

	
}

TEST(posl_test, constr_copy) {
	size_t size = 1;
	p_cont <int> testV(size);
	testV.pushback(10);
	testV.pushback(20);
	testV.pushback(30);
	
	p_cont <int> testV2(size++);
	testV2 = testV;

	EXPECT_EQ(testV[0], testV2[0]);
	
	EXPECT_EQ(testV[1], testV2[1]);
	
	EXPECT_EQ(testV[2], testV2[2]);
	
	EXPECT_EQ(testV[3], testV2[3]);
	
}
TEST(posl_test, clear_dyn_mem_test) {
	

	static int delet_count = 1;// MyStruct a - budet udelen posle zavershenia programmi

	struct MyStruct
	{
		int xxxx = 1;
		~MyStruct() {

			delet_count--;
		}

		MyStruct() {

			delet_count++;
		}
	};
	{
		MyStruct a;
		size_t size = 1;
		p_cont <MyStruct> testV(size);
		testV.pushback(a);
		testV.erase(1);
	}
	
	
	
	
	
	EXPECT_EQ(delet_count, 0);
	


}