#include<iostream>
#include<ctime>
#include<chrono>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

#define delimiter "\n-----------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool isLeaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i);
	}
	Tree(const Tree& other) :Tree()
	{
		Copy(other.Root);
	}
	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth()const
	{
		return Depth(Root);
	}
	void Clear()
	{
		Clear(Root);
	}
	void Copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		Copy(Root->pLeft);
		Copy(Root->pRight);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;

		int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;

		/*return Root == nullptr ? 0 :
			Depth(Root->pLeft) + 1 >
			Depth(Root->pRight) + 1 ?
			Depth(Root->pLeft) + 1 :
			Depth(Root->pRight) + 1;*/
			/*if (Root == nullptr)return 0;
			if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)return Depth(Root->pLeft) + 1;
			else return Depth(Root->pRight) + 1;*/
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define TIME_MESUREMENT

#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n = 100000;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;

#ifdef TIME_MESUREMENT
	cout << typeid(std::chrono::steady_clock::now()).name() << endl;
	std::chrono::steady_clock::time_point ch_start = std::chrono::steady_clock::now();
	clock_t c_start = clock();
	static time_t t_start = time(NULL);
#endif // TIME_MESUREMENT

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}

#ifdef TIME_MESUREMENT
	///////////////////////		Time:		///////////////////////
	std::chrono::steady_clock::time_point ch_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> delta = ch_end - ch_start;
	clock_t c_end = clock();
	static time_t t_end = time(NULL);
	cout << delimiter << endl;
	cout << "elapsed time chrono:  " << delta.count() << endl;
	cout << "elapsed time time():  " << t_end - t_start << endl;
	cout << "elapsed time clock(): " << double(c_end - c_start) / CLOCKS_PER_SEC << endl;
	cout << delimiter << endl;
	//-------------------------------------------------------------  
#endif // TIME_MESUREMENT

	//tree.print();
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;

#ifdef TIME_MESUREMENT
	system("PAUSE");
	//////////////////////////////////////////////////////////////////////////////////////////
	ch_start = std::chrono::steady_clock::now();
	t_start = time(NULL);
	c_start = clock();
#endif

	cout << "Количество элементов дерева: " << tree.Count() << endl;

#ifdef TIME_MESUREMENT
	ch_end = std::chrono::steady_clock::now();
	t_end = time(NULL);
	c_end = clock();
	cout << delimiter << endl;
	delta = ch_end - ch_start;
	cout << "elapsed time chrono:  " << delta.count() << endl;
	cout << "elapsed time time():  " << t_end - t_start << endl;
	cout << "elapsed time clock(): " << double(c_end - c_start) / CLOCKS_PER_SEC << endl;
	cout << delimiter << endl;
	//////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////
	ch_start = std::chrono::steady_clock::now();
	t_start = time(NULL);
	c_start = clock();
#endif // TIME_MESUREMENT

	//cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

#ifdef TIME_MESUREMENT
	ch_end = std::chrono::steady_clock::now();
	t_end = time(NULL);
	c_end = clock();
	cout << delimiter << endl;
	delta = ch_end - ch_start;
	cout << "elapsed time chrono:  " << delta.count() << endl;
	cout << "elapsed time time():  " << t_end - t_start << endl;
	cout << "elapsed time clock(): " << double(c_end - c_start) / CLOCKS_PER_SEC << endl;
	cout << delimiter << endl;
	//////////////////////////////////////////////////////////////////////////////////////////


#endif // TIME_MESUREMENT

	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

#ifdef TIME_MESUREMENT
	//system("PAUSE");
//cout << "Время подсчета: " << difftime(t_end, t_start) << " c" << endl;
//cout << "Время подсчета: " << t_end - t_start << " c" << endl;
//cout << start << endl;
//cout << end << endl;
//cout << "Время подсчета: " << double(end - start) / CLOCKS_PER_SEC << endl;  
#endif // TIME_MESUREMENT

	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100);
	}
	/*while (tree2.Count(tree2.getRoot()) < n)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}*/
	//tree2.print(tree2.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree2.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree2.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree2.Count() << endl;
	cout << "Сумма элементов дерева: " << tree2.Sum() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree2.Avg() << endl;
	cout << "Глубина дерева: " << tree2.Depth() << endl;
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 48, 49, 85, 91, 58, 68, 67 };
	tree.print();
	cout << "Глубина дерева: " << tree.Depth() << endl;
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();

	/*Tree tree2 = tree;
	tree2.print();*/
#endif // DEPTH_CHECK
}