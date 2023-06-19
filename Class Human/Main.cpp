#include<iostream>
#include<string>

using namespace std;

class Human 
{
public:
	string HumanName;
	string HumanSurname;
	string HumanGender;
	int HumanAge;
	Human(string name, string surname, string gender, int age)
	{
		HumanName = name;
		HumanSurname = surname;
		HumanGender = gender;
		HumanAge = age;
	}
};

class Student : public Human
{
public:
	string university;
	string faculty;
	int course;
	Student(string name, string surname, string gender, int age, string universit, 
		string facult, int cours) : Human(name, surname, gender, age)
	{
		university = universit;
		faculty = facult;
		course = cours;
	}
	Student(Human A, string universit, string facult, int cours) : Human(A.HumanName, 
		A.HumanSurname, A.HumanGender, A.HumanAge)
	{
		university = universit;
		faculty = facult;
		course = cours;
	}
	friend ostream& operator<<(ostream& os, const Student& s) 
	{
		os << s.HumanName << " " << s.HumanSurname << " , " << s.HumanAge << " yeras old, gender - "
			<< s.HumanGender << " , student of " << s.university << " university, on the "
		    << s.course << " cours of " << s.faculty << " faculty." << endl;
		return os;
	}
};

void main()
{
	Human A("Bob", "Johnson", "Male", 20);
	Student s1(A, "Harvard", "FAM", 3);
	cout << s1 << endl;
	Human B("Kate", "Gordon", "Female", 21);
	Student s2(B, "Harvard", "FAM", 4);
	cout << s2 << endl;
}