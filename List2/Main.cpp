#include<iostream>
using namespace std;

#define tab "\t"

//#define BASE_CHECK

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	unsigned int size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return *this;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReversIterator
	{
		Element* Temp;
	public:
		ReversIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			//cout << "RItConstructor\t" << this << endl;
		}
		~ReversIterator()
		{
			//cout << "RItDestructor\t" << this << endl;
		}
		ReversIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReversIterator operator++(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pPrev;
			return *this;
		}
		ReversIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReversIterator operator--(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pNext;
			return *this;
		}
		bool operator==(const ReversIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReversIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReversIterator rbegin() 
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConsrtuctor\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	//             Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}

		//Element* New = new Element(Data);     //1)
		//New->pNext = Head;				    //2)
		//Head->pPrev = New;					//3)
		//Head = New;							//4)
		//size++;
    				    
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);   
		New->pPrev = Tail;				    
		Tail->pNext = New;					
		Tail = New;							
		size++;*/
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;*/

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void insert(int Index, int Data)
	{
		if (Index > size)return;
		//if (Index == 0)return push_front(Data);
		Element* Temp;
		if(Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//Element* New = new Element(Data);
		//New->pNext = Temp;
		//New->pPrev = Temp->pPrev;
		//Temp->pPrev->pNext = New;
		//Temp->pPrev = New;
		//size++;
	
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//             Removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//             Methods:
	void print()
	{
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
		}
		cout << "Реверс элементов: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for(List::ReversIterator rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
}