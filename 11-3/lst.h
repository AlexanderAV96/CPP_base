#pragma once

#include <iostream>
using std::cout;

template<typename V>
class MyList
{
public:
	int getsize() { return size; }
	void popfront();
	void pushback(V data);
	void insert(V data, int place);
	void remove(int place);
	V& operator [](int place);
	void print();
	void pushfront(V data);

	MyList();
	~MyList();

private:



	template<typename V>
	class Link {
		;
	public:


		Link <V>* next;
		V data;

		Link(V data = V(), Link* next = nullptr) {

			this->data = data;
			this->next = next;

		};

	};

	Link <V>* first;
	int size;

};


