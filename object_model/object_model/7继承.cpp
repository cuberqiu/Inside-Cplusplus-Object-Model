//继承

/*
	继承中构造函数和析构函数调用的次序：
	构造函数：自顶（基类）向下（派生类）构造，即先构造基类，再构造派生类
	析构函数：自底（派生类）向上（基类）析构，即先析构派生类，再析构基类
*/

#include<iostream>

using namespace std;

class Base
{
public:
	Base(int b) :b1{ b } { cout << "Base is constructed..." <<"b1="<< b1 << endl; }
	~Base() { cout << "Base is destructed" << endl; }
	void f(int i) { cout << "Base::f(int i)" << endl; }
	void f(string s) { cout << "Base::f(string s)" << endl; }
	Base& operator=(const Base&);
	int operator=(int a) { return 8; }
			//构造函数、析构函数以及重载赋值运算符都不能继承到派生类之中
	Base& operator++() { ++this->b1; return *this; }

public:
	int b1;
};

Base& Base::operator=(const Base& b)
{
	this->b1 = b.b1;
	return *this;
}

class Derived1 :public Base {
public:
	Derived1(int d) :Base(d), d1{d}, b1(d), b2(d){ 
		cout << "Derived1 is constructed..." << "d1=" << d << endl; 
		b2 = b1;
	}
					//构造函数的初始化列表：在没有对所有成员对象和基类对象的构造函数进行调用之前，无法进入该构造函数体。
					//C++中认为，所有成员对象在构造函数的左括号之前就被初始化了，一旦遇到左括号，则认为所有子对象均被正确
					//初始化。
	~Derived1() { cout << "Derived1 is destructed" << endl; }
	 //Derived1& operator=(Derived1&) = delete;
private:
	int d1;
	Base b1;
	Base b2;
public:
	void f(int i) { cout << "Derived1::f(int i)" << endl; }
			//名字隐藏：任何时候重新定义了基类的一个重载函数，在新类中的所有其他的版本则被自动隐藏
								//即，Base中的void f(string s)在其派生类Derived1中被隐藏，无法使用

};

class Derived2 :public Derived1 {
public:
	Derived2(int d) :Derived1(d), d2{ d }, b(d) { cout << "Derived2 is constructed..." << "d2=" << d << endl; }
	~Derived2() { cout << "Derived2 is destructed" << endl; }
private:
	int d2;
	Base b;
};

class Base7
{
	virtual void b_func1() {}
	virtual void b_func2() {}
	void b_func3() {}
};

class Derived71 :public Base7
{
	virtual void d1_func1() {}
	virtual void d1_func2() {}
};

class Derived72 :virtual public Base7
{
	virtual void d2_func1() {}
	virtual void d2_func2() {}
	virtual void d2_func3() {}
	virtual void d2_func4() {}
};

void TestClass()
{
	Base b1{ 1 }, b2{ 2 };
	b1.b1 = b2.b1;
	cout << "b1=" << b1.b1 << endl;
	Derived2 d(1);
	Derived1 d1(2);
	Derived1 d2(3);
	d2 = d1;  //调用了基类的operator=
}

void main7()
{
	Derived71 d71;
	Derived72 d72;
	static Base7 b1;
	void* p = &b1;
	//不能用void*型指针来操作对象，因为void*的指针只能够含有一个地址（一个首地址），但是我们不能知道他的地址空间（即地址从哪到哪）
	cout << "sizeof(Derived71)=" << sizeof(Derived71) << endl;
	cout << "sizeof(Derived72)=" << sizeof(Derived72) << endl;
	cout << "sizeof(static Base7)=" << sizeof(b1) << endl;
	TestClass();
	system("pause");
}

/*
	运行结果：
	Base is constructed...b1 = 1
	Base is constructed...b1 = 1
	Derived1 is constructed...d1 = 1
	Base is constructed...b1 = 1
	Derived2 is constructed...d2 = 1
	Derived2 is destructed
	Base is destructed
	Derived1 is destructed
	Base is destructed
	Base is destructed
*/