#include"ForwardList.h"
///////////////////////////////////////////////////////////////
////////////////////// CLASS DEFINITION //////////////////////


template<typename T>int Element<T>::count = 0;	//Инициализируем статическу переменную, объявленную в классе 'Element'

template<typename T>Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>Element<T>::~Element()
{
	count--;
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}
/////////////
template<typename T>Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>Iterator<T>::~Iterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->Temp != other.Temp;
}
// type functionName(parameters)
template<typename T>T& Iterator<T>::operator*()
{
	return Temp->Data;
}
//////////////////////////////////////
template<typename T>Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
template<typename T> ForwardList<T>::ForwardList()
{
	Head = nullptr;	//Если список пуст, то его Голова указывает на 0
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{

	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//					Adding elements:
template<typename T>void ForwardList<T>::push_front(T Data)
{
	Head = new Element<T>(Data, Head);
	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);

	Element<T>* Temp = Head;
	while (Temp->pNext)
		Temp = Temp->pNext;

	Temp->pNext = new Element<T>(Data);
	size++;
}
template<typename T>void ForwardList<T>::insert(int Index, T Data)
{
	if (Index == 0)return push_front(Data);
	if (Index > size)return;

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

	Temp->pNext = new Element<T>(Data, Temp->pNext);

	size++;
}

//					Erasing Elements
template<typename T>void ForwardList<T>::pop_front()
{
	Element<T>* Erased = Head;	//1) запоминаем адрес удаляемого элемента
	Head = Head->pNext;		//2) исключаем элемент из стписка
	delete Erased;			//3) удаляем элемент из памяти

	size--;
}

template<typename T>void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}

//					Methods:
template<typename T>void ForwardList<T>::print()const
{
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

	cout << "Количество элементов списка:" << size << endl;
	cout << "Общее количество элементов: " << Element::count << endl;
}

//////////////////////// CLASS DEFINITION END///////////////////
///////////////////////////////////////////////////////////////