#include<iostream>

using namespace std;

//discuss the pointer to member function

class Student
{
public:
	Student(int num) :num_{ num } {}
	virtual void func1() {}
	void func2() 
	{
		cout << "this=" << this << endl; 
	}
public:
	int num_;
};

void main()
{
	Student s1(1);
	int *pint = &s1.num_;
	cout << "&s1=" << &s1 << endl;
	s1.func2();
	cout << "boob" << endl;

}