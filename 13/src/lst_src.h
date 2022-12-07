
#include "lst.h"


template<typename V>
MyList<V>::MyList() {
	first = nullptr;
	size = 0;
	lst_count++;

};

template<typename V>
void MyList<V>::pushback(V data) {

	if (first == nullptr) { first = new Link <V>(data); }// otdelno dlya 1 tak kak ukazatel == nullptr
	else {

		Link<V>* tmp = this->first;

		while (tmp->next != nullptr)  // dohodim do poslednego
		{
			tmp = tmp->next;
		}
		tmp->next = new Link <V>(data);
	}

	this->size++;
}
//template<typename V>
//V& MyList<V>::operator [](int place) {
//
//
//	int i = 0;
//	Link <V>* tmp = this->first;
//
//	while (tmp != nullptr) { // do kontsa
//
//		if (i == place)
//		{
//			return tmp->data; // esli sovpadaet to vozvrashaem dannie
//		}
//
//		tmp = tmp->next;
//		i++;
//	}
//}
template<typename V>
const V& MyList<V>:: operator [](const int place) const {


	int i = 0;
	Link <V>* tmp = this->first;

	while (tmp != nullptr) { // do kontsa

		if (i == place)
		{
			return tmp->data; // esli sovpadaet to vozvrashaem dannie
		}

		tmp = tmp->next;
		i++;
	}


};


template<typename V>
V&  MyList<V>:: operator  [](const int place)  {


	int i = 0;
	Link <V>* tmp = this->first;

	while (tmp != nullptr) { // do kontsa

		if (i == place)
		{
			return tmp->data; // esli sovpadaet to vozvrashaem dannie
		}

		tmp = tmp->next;
		i++;
	}
}

template<typename V>
void MyList <V>::print() {

	/*for (int i = 0; i < getsize();i++) {

		std::cout << this[i] << '\t';

	}
	std::cout << '\n';*/

	
	Link <V>* tmp = this->first;

	for (int i = 0; i < this->getsize();i++) { // do kontsa

		
		std::cout<< tmp->data; // esli sovpadaet to vozvrashaem dannie
		std::cout << '\t';
		tmp = tmp->next;
		
	}
	std::cout << '\n';
}

template<typename V>
void MyList <V>::popfront() {

	Link <V>* tmp = first;
	first = first->next;

	delete tmp;
	this->size--;

}
template<typename V>
void MyList <V>::remove(int place) {

	if (place == 1) { popfront(); }
	else
	{
		Link <V>* prev = first;

		for (int i = 0; i < (place - 2); i++) {
			prev = prev->next;
		}
		Link <V>* tmp = prev->next;

		prev->next = tmp->next;

		delete tmp;

		this->size--;
	}


}

template<typename V>
void MyList<V> ::pushfront(V data) {

	first = new Link <V>(data, first);

	size++;

}



template<typename V>
void MyList<V>::insert(V data, int place) {

	if (place == 1) { pushfront(data); }
	/*else if (place == getsize()) {
		pushback(data);
	}*/
	else
	{
		Link<V>* prev = this->first;

		for (int i = 0; i < (place - 2);i++)
		{
			prev = prev->next;
		}

		Link<V>* tmp = new Link <V>(data, prev->next);
		prev->next = tmp;
		//prev->next = tmp;

		size++;
	}





}
//template<typename V>
//V& MyList<V>::operator =(const MyList <V> & other) {
//
//	if (this->size > 0) { for (int i = 0; i < this->size;i++) this->popfront(); }
//	
//	this->first->data = other.first->data;
//	this->first->next = nullptr;
//	this->size = 1;
//	//V tmp;
//	
//	for (int i = 1; i < size;i++) {
//
//		//tmp = other[i];
//		//this->pushback(tmp);
//	}
//
//
//};