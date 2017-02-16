//This .cc is used to introduce the C++ obeject model

#include<iostream>
#include<string>

using namespace std;

class Point{
public:
	Point(float xval);      //constructor
	virtual ~Point();        //virtual destructor
	float x() const;          //const member function
	static int PointCount();     //static member function
private:
	virtual ostream& print(ostream& os) const;     //virtual const member function
	float x_;      //member data
	static int point_count_;    //static member data
};

//struct and class
struct C_point {};   //define a struct

class MyPiont {     //define a class
public:
	C_point c_point() { return c_point_; }
private:
	//this is composition
	C_point c_point_;  //using struct in class, we use struct to package the data
};

//An object distinction
//1.procedural model
void func1()
{
	char boy[] = "bobo";
	char *p_son;
	p_son = new char[strlen(boy) + 1];
	strcpy(p_son, boy);
	delete p_son;
}

//default constructor is produced when it is needed.
class DefaultFunctionClass{
public:  //no explicit constructor
	int a;
	int* p;
};

void test_default()
{
	DefaultFunctionClass d1; //no expilcit constructor

	//the default constructor will not initialize the d1.a=0
	cout <<"d1.a="<< d1.a << endl;// The variable 'd1' is being used without being initialized.

	if (d1.p == nullptr) // The variable 'd1' is being used without being initialized.
		d1.p = 0;
}

class Foo
{
public:
	Foo() {}
	Foo(int) {}
};

class Bar
{
public:
	Foo foo;   //not inherit £¬it`s  include
	char* str;
};

void foo_bar()
{
	Bar bar; //Bar::foo must be initialized here
					//Bar::foo is a member class object £¬and it has default costructors
}

//Bar`s default constructor may be as follow
//inline Bar::Bar()
//{
//	//the C++ pseudo code
//	foo.Foo::Foo();
//}


void main_object()
{
	//test();
	// test_word();
	cout << "HeartCraft" << endl;
}