#include<iostream>
#include<ctime>
using namespace std;

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
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "DConstructor:\t" << this << endl;
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
		//cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		//cout << "TDrestructor:\t" << this << endl;
	}
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
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

	//int minValue(Element* Root)
	//{
	//	if (Root == nullptr)
	//		return INT_MAX;
	//	int leftMin = minValue(Root->pLeft);
	//	int rightMin = minValue(Root->pRight);
	//	return min(Root->Data, min(leftMin, rightMin));
	//}
	int minValue(Element* Root)
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)
	{
		if (Root == nullptr) return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)
	{
		if (Root == nullptr) return 0;
		else return Root->Data + sum(Root->pLeft) + sum(Root->pRight);
	}
	double avg()
	{
		return (double)sum(Root) / count(Root);
	}
	int depth(Element* Root)
	{
		if (Root == nullptr) return 0;
		else
		{
			int leftDepth = depth(Root->pLeft);
			int rightDepth = depth(Root->pRight);
			if (leftDepth > rightDepth) return leftDepth + 1;
			else return rightDepth + 1;
		}
	}
	

	void erase(int Data, Element* Root)
	{
		Element* parent = nullptr;
		Element* current = Root;
		while (current != nullptr && current->Data != Data)
		{
			parent = current;
			if (Data < current->Data)
			{
				current = current->pLeft;
			}
			else
			{
				current = current->pRight;
			}
		}
		if (current == nullptr)
		{
			return;
		}
		if (current->pLeft == nullptr && current->pRight == nullptr)
		{
			if (current == Root)
			{
				Root = nullptr;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = nullptr;
			}
			else
			{
				parent->pRight = nullptr;
			}
			delete current;
		}
		else if (current->pLeft == nullptr)
		{
			if (current == Root)
			{
				Root = current->pRight;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = current->pRight;
			}
			else
			{
				parent->pRight = current->pRight;
			}
			delete current;
		}
		else if (current->pRight == nullptr)
		{
			if (current == Root)
			{
				Root = current->pLeft;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = current->pLeft;
			}
			else
			{
				parent->pRight = current->pLeft;
			}
			delete current;
		}
		else
		{
			Element* minParent = current;
			Element* min = current->pRight;
			while (min->pLeft != nullptr)
			{
				minParent = min;
				min = min->pLeft;
			}
			current->Data = min->Data;
			if (minParent->pLeft == min)
			{
				minParent->pLeft = min->pRight;
			}
			else
			{
				minParent->pRight = min->pRight;
			}
			delete min;
		}
	}
	
};

class UniqueTree :public Tree
{
public:
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
	double avg()
	{
		return (double)sum(Root) / count(Root);
	}
	int depth(Element* Root)
	{
		if (Root == nullptr) return 0;
		else
		{
			int leftDepth = depth(Root->pLeft);
			int rightDepth = depth(Root->pRight);
			if (leftDepth > rightDepth) return leftDepth + 1;
			else return rightDepth + 1;
		}
	}
	void erase(int Data, Element* Root)
	{
		Element* parent = nullptr;
		Element* current = Root;
		while (current != nullptr && current->Data != Data)
		{
			parent = current;
			if (Data < current->Data)
			{
				current = current->pLeft;
			}
			else
			{
				current = current->pRight;
			}
		}
		if (current == nullptr)
		{
			return;
		}
		if (current->pLeft == nullptr && current->pRight == nullptr)
		{
			if (current == Root)
			{
				Root = nullptr;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = nullptr;
			}
			else
			{
				parent->pRight = nullptr;
			}
			delete current;
		}
		else if (current->pLeft == nullptr)
		{
			if (current == Root)
			{
				Root = current->pRight;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = current->pRight;
			}
			else
			{
				parent->pRight = current->pRight;
			}
			delete current;
		}
		else if (current->pRight == nullptr)
		{
			if (current == Root)
			{
				Root = current->pLeft;
			}
			else if (parent->pLeft == current)
			{
				parent->pLeft = current->pLeft;
			}
			else
			{
				parent->pRight = current->pLeft;
			}
			delete current;
		}
		else
		{
			Element* minParent = current;
			Element* min = current->pRight;
			while (min->pLeft != nullptr)
			{
				minParent = min;
				min = min->pLeft;
			}
			current->Data = min->Data;
			if (minParent->pLeft == min)
			{
				minParent->pLeft = min->pRight;
			}
			else
			{
				minParent->pRight = min->pRight;
			}
			delete min;
		}
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	int n; int q;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << "\n����������� �������� � ������: " << tree.minValue(tree.getRoot()) << endl;
	cout << "\n������������ �������� � ������: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "\n���������� ��������� � ������: " << tree.count(tree.getRoot()) << endl;
	cout << "\n����� ��������� � ������: " << tree.sum(tree.getRoot()) << endl;
	cout << "\n������� �������������� ��������� ������: " << tree.avg() << endl;
	cout << "\n������� ������: " << tree.depth(tree.getRoot()) << endl;
	cout << "������� ��������� ������� ������: "; cin >> q;
	tree.erase(q, tree.getRoot());
	cout << "������ ����� ��������:\n";
	tree.print(tree.getRoot());
	cout << endl;
	//tree.clear(tree.getRoot());


	cout << endl;
	UniqueTree tree2;
	/*for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}*/
	while(tree2.count(tree2.getRoot()) < n)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}
	tree2.print(tree2.getRoot());
	tree2.clear();
	cout << "\n����������� �������� � ������: " << tree2.minValue(tree2.getRoot()) << endl;
	cout << "\n������������ �������� � ������: " << tree2.maxValue(tree2.getRoot()) << endl;
	cout << "\n���������� ��������� � ������: " << tree2.count(tree2.getRoot()) << endl;
	cout << "\n����� ��������� � ������: " << tree2.sum(tree2.getRoot()) << endl;
	cout << "\n������� �������������� ��������� ������: " << tree2.avg() << endl;
	cout << "\n������� ������: " << tree2.depth(tree.getRoot()) << endl;
	cout << "\n������� ��������� ������� ������: "; cin >> q;
	tree2.erase(q, tree2.getRoot());
	cout << "\n������ ����� ��������:\n";
	tree2.print(tree2.getRoot());
	cout << endl;
	tree2.print(tree2.getRoot());
}