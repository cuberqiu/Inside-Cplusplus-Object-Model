#include<iostream>

using namespace std;

//discuss the pointer to member function

class BaseStudent
{
public:
	virtual void virtual_func1() { cout << "BaseStudent::virtual func1()" << endl; }
};


/*this pointer:
	nonstatic member function has this pointer.
	static class members do not have this pointer.
	this pointer is not one part of an object, it will not influence the result of sizeof()
	the value of this pointer is the address of an object.
*/
class Student:public BaseStudent
{
	//member function do not bind with any object, all the object share one function code instance
	//in member function ,when need acssess the nonstatic member data ,it needs this pointer
public:
	Student(int num) :num_{ num } {}
	virtual void virtual_func1() { cout << "Student::virtual func1()" << endl; }
	virtual void virtual_func2() { cout << "Student::virtual func2()" << endl; }

	void nonstatic_func1() { cout << "Student::nonstatic func1()" << endl; }
	void nonstatic_func2() { cout << num_ << "Student::nonstatic func2()" << endl; }

	static void static_func1() { cout << "Student::static func1()" << endl; }
	static void static_func2() { cout << "Student::static func2()" << endl; }

	void this_func() 
	{//this pointer only can be used in class member function
		//it`s action scope is in the class
		cout << "this=" << this << endl; 
	}

	static void static_func()
	{
		//num_ = 10;   //error: static member function can not read/write nonstatic member data
		static_num_ = 10; //static member function can read/write nonstatic memberdata
	}
	void nonstatic_func()
	{
		//nonstatic member function can read/write nonstatic/static member data
		num_ = 1;
		static_num_ = 0;
	}
public:
	int num_;
	static int static_num_;
};

int Student::static_num_ = 0;

void test_student_this()
{
	Student s1(1);
	int *pint = &s1.num_;
	cout << "&s1=" << &s1 << endl;
	s1.this_func();
	//s1.(this->num_);    //error: this pointer only can be used in class member function
	/*result:
	Student s1(1);
	int *pint = &s1.num_;
	cout << "&s1=" << &s1 << endl;
	s1.func2();
	*/
}

//Pointer to member function
//pointer to nonstatic member function
typedef void (Student::*ptr_nonstatic_func)();
//pointer to static member function
typedef void(*ptr_static_func)();

void test_member_func_ptr()
{
	Student* s = nullptr;
	s->nonstatic_func1();	//Student::nonstatic func1() ,it doesn`t use this pointer
	//s->nonstatic_func2();   //error, it need use this pointer
	s->static_func1();	//Student::static func1(),it doesn`t usr this pointer
	//s->virtual_func1();	 //error, it is virtual function ,and will produce a member data: vbptr,so need use this pointer

	Student s1(1);
	ptr_nonstatic_func ptr_nonstatic = &Student::nonstatic_func1;
	ptr_nonstatic_func ptr_virtual = &Student::virtual_func1;
	ptr_static_func ptr_static = &Student::static_func2;
	
	(s1.*ptr_nonstatic)();//using nonstatic member function pointer need an object;
	(s1.*ptr_virtual)();
	ptr_static();//using static member function do not need an object 
	/*result:
		Student::nonstatic func1()
		Student::static func2()
	*/

	//member function pointer in inherent£¬virtual mechnism is valid
	void (BaseStudent::* pbase)() = &BaseStudent::virtual_func1;
	BaseStudent* p_to_d = new Student(1);
	p_to_d->virtual_func1();
	(p_to_d->*pbase)();
	/*result:
		Student::virtual func1()
		Student::virtual func1()
	*/
}


void main_function()
{
	//Student* s = nullptr;
	//s->nonstatic_func1();
	//s->virtual_func1();
	test_member_func_ptr();
	cout << "boob" << endl;
}