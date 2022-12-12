#pragma once

#include <iostream>
using std::cout;

static int lst_count = 0;

template<typename V>
class MyList
{
public:
	
	//const V& operator [](int place) const ;
	//MyList& operator =(const MyList& other) const;
	V& operator  [](const int place);
	const V& operator [](const int place) const ;

	int getsize() { return size; }
	void popfront();
	void pushback(V data);
	void insert(V data, int place);
	void remove(int place);


	void print();
	void pushfront(V data);
	MyList() ;
	
	MyList(const MyList& other) {
		
		this->first->data = other.first->data;
		this->first->next = nullptr;
		this->size = other.size;
		
		for (int i = 1; i < size;i++) {

			this->insert(other[i], i);
			//this->pushback(other[i]);
		}
		//lst_count++;
	}

	MyList& operator =(const MyList& other) {
		
		if (this->size > 1) { for (int i = 1;i < this->size;i++) this->popfront(); }
		
		
		this->first->data = other.first->data;
		this->first->next = nullptr;
		//this->size = other.size;

		for (int i = 1; i < other.size;i++) {

			//this->insert(other[i], i);
			this->pushback(other[i]);
		}
		return *this;
	}



	V& operator =( const V& other) {


		this->first->data = other.first->data;
		this->first->next = nullptr;
		this->size = other.size;

		for (int i = 1; i < size;i++) {

			this->insert(other[i], i);
			
		}
		return *this;
	}

	/* MyList& operator =(const MyList& other) const {

				
		this->first->data = other.first->data;
		this->first->next = nullptr;
		this->size = other.size;

		for (int i = 1; i < size;i++) {

			this->insert(other[i], i);
				
		}
		return *this;
	}*/
		
	~MyList() {
		while (size) {
			popfront(); lst_count--;
	} };

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


