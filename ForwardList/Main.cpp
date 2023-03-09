#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList  //Однонаправленный
{
	Element* Head; //Содержит указатель на нулевой элемент списка
public:
	ForwardList()
	{
		Head = nullptr; //Если список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//             Adding elements
	void push_front(int Data)
	{
		//1. Создаем новый элемент
		Element* New = new Element(Data);
		//2. Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3. Голову спска "переводим" на новый элемент
		Head = New;
	}

	//             Metods
	void print()const
	{
		Element* Temp = Head;
		//Temp - итератор - указатель, 
		//при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Создаем новый элемент
		Element* New = new Element(Data);
		// Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//3.Добавляем элемент в конец спска
		Temp->pNext = New;

	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка:	"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100); //Для работы с пустым списком добавили строку 61
	}
	list.print();
	//list.push_back(123);
	//list.print();
}