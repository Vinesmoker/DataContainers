#pragma once
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

///////////////////////////////////////////////////////
////////////// CLASS DECLORATION //////////////////////


template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>class Element
{
	T Data;		//значение элемента
	Element<T>* pNext;	//адрес следующего элемента
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
	friend class ForwardList<T>;
	friend class Iterator<T>;
};


template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr);

	~Iterator();


	Iterator& operator++();


	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	T& operator*();
};
template<typename T>class ForwardList	//Forward - односв€зный, однонаправленный
{
	Element<T>* Head;	//√олова списка - содержит указатель на нулевой элемент списка
	int size;
public:
	Iterator<T> begin();
	Iterator<T> end();
	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	~ForwardList();

	//					Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);

	//					Erasing Elements
	void pop_front();
	void pop_back();

	//					Methods:
	void print()const;
};
////////////////////// CLASS DELORATION END////////////////////
///////////////////////////////////////////////////////////////