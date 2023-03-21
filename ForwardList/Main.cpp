#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;	//�������������� ���������� ����������, ����������� � ������ 'Element'

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		//cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		//cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int)
	{
		Temp = Temp->pNext;
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

class ForwardList	//Forward - �����������, ����������������
{
	Element* Head;	//������ ������ - �������� ��������� �� ������� ������� ������
	int size;
public:
	Iterator begin()
	{
		return Head;
	}
	const Iterator begin()const
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	const Iterator end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;	//���� ������ ����, �� ��� ������ ��������� �� 0
		size = 0;
		//cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//il - initializer_list
		//initializer_list - ��� ���������.
		//��������� - ��� ������, ������� ���������� �������� ������ �������� � ������.
		//��� � � ������ ������� ����������, � initilizer_list ���� ������ begin() � end()
		//begin() - ���������� �������� �� ������ ����������.
		//end()   - ���������� �������� �� ����� ����������.
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		//cout << "LDestructor:\t" << this << endl;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		/*
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ����� ������� ������ ��������� �� ������ ������:
		New->pNext = Head;
		//3) ������ ������ "���������" �� ����� �������:
		Head = New;
		*/

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		//Element* New = new Element(Data);
		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//3) ��������� ������� � ����� ������:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//1) ������� ����� �������:
		//Element* New = new Element(Data);

		//2) ������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) ��������� ����� ������� � ������:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
	}

	//					Erasing Elements
	void pop_front()
	{
		Element* Erased = Head;	//1) ���������� ����� ���������� ��������
		Head = Head->pNext;		//2) ��������� ������� �� �������
		delete Erased;			//3) ������� ������� �� ������

		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//					Methods:
	void reverse()
	{
		ForwardList buffer;
		while(Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		Head = buffer.Head;
		buffer.Head = nullptr;
	}
	void print()const
	{
		/*Element* Temp = Head;	//Temp - ��� ��������
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������
		//� ��������� ��������� ������
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "���������� ��������� ������:" << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;
	}
};

ForwardList operator+(const ForwardList & left, const ForwardList& right)
{
	ForwardList cat;
	for (Iterator it = left.begin(); it != left.end(); it++)cat.push_back(*it *= 10);
	for (Iterator it = right.begin(); it != right.end(); it++)cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define HOME_WORK_1
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);

	int value;
	int index;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	//Range-based for
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef HOME_WORK_1
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl;

	for (int i : list)cout << i << tab; cout << endl;

#endif // HOME_WORK_1

#ifdef PERFORMANCE_CHECK
	ForwardList list;
	int n;
	cout << "������� ������ ������: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << "������ ��������!" << endl;
	ForwardList list2 = list;
	//for (int i : list)cout << i << tab; cout << endl;
	//for (int i : list2)cout << i << tab; cout << endl;  
#endif // PERFORMANCE_CHECK



}