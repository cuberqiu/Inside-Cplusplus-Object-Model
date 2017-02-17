//多态
/*
	参考链接：
	http://blog.jobbole.com/101583/
	http://www.cnblogs.com/clor001/p/3313589.html
	http://www.cnblogs.com/clor001/p/3329652.html
	《C++大学教程》P470~P472
	《C++编程思想》第一卷 第15章
*/

/*
	静态绑定：
	编译时绑定，通过对象调用；当成员函数或者virtual函数通过按名引用特定对象或
	使用圆点成员选择运算符被调用时，调用哪个函数在编译时就已经决定了。

	动态绑定：
	运行时绑定，通过地址实现；如果程序通过指向派生类的基类指针或者指向派生类
	对象的基类引用调用虚函数，那么程序会根据所指对象的类型而不是指针的类型，
	动态的选择正确的派生类函数。在执行时选择合适的调用函数成为动态绑定。

	**将基类指针指向派生类对象后，试图通过该基类指针调用仅在派生类含有的成员将导致编译错误。

	**不要在构造函数和析构函数中调用虚函数，若调用了，将不实行虚机制。

	**构造函数不能使虚函数：
	1.从存储角度来讲：
	构造函数是在创建一个类对象时才调用，且vfptr存储在类对象的内存中，若不执行构造函数，
	将不会生成vfptr，而虚函数是通过vfptr来调用的，如果构造函数是虚的，就需要通过 vtable来调用，
	可是对象还没有实例化，也就是内存空间还没有，怎么找vtable呢？所以构造函数不能是虚函数。
	2.从实现角度来看：
	vfptr在构造函数调用后才建立，因而构造函数不可能成为虚函数，而且构造函数的作用是提供初始化，
	在对象生命期只执行一次，不是对象的动态行为，也没有必要成为虚函数
*/
#include<iostream>
#include<typeinfo>

using namespace std;

class MyBase 
{
public:
	MyBase(int i) :b{ i } { cout << "Base construct" << endl; }
	  ~MyBase() { cout << "Base destruct" << endl; }
	virtual void func1() { cout << "Base::func1()" << endl; }
	virtual void func2() { cout << "Base::func2()" << endl; }
	virtual void func3() { cout << "Base::func3()" << endl; }
private:
	int b;
};

class MyBase1
{
public:
	MyBase1(int i) :b{ i } { cout << "Base1 construct" << endl; }
	~MyBase1() { cout << "Base1 destruct" << endl; }
	virtual void func1() { cout << "Base1::func1()" << endl; }
	virtual void func2() { cout << "Base1::func2()" << endl; }
	virtual void func3() { cout << "Base1::func3()" << endl; }
private:
	int b;
};

class MyDerived1:public MyBase
{
public:
	MyDerived1(int d) :d1{ d }, MyBase(d){ 
		func1();//执行结果为：Derived1::func1()
/*
	在构造函数中调用虚函数，虚机制在构造函数中不工作
	原因：构造函数的工作是生成一个对象，在任何构造函数中，可能只是部分形成对象——我们
	只能知道基类已被初始化，但并不知道哪个类是从这个基类继承而来的。然而虚函数在继承层次上
	是“向前”和“向外”进行调用。它可以调用在派生类中的函数。如果我们在构造函数中也这样做，会
	有可能调用未被初始化的成员，这将导致灾难后果。
	同时，VFPTR的状态是由被最后调用的构造函数确定的。这就是为什么构造函数的调用时从基类到派生类。
*/
		cout << "Derived1 construct" << endl; }
	 ~MyDerived1() {
		//MyBase::func1();
		cout << "Derived1 destruct" << endl; 
	}
/*析构函数可以是虚函数
	这个对象已经知道它是什么类型（而在构造的时候不知道），一旦对象已构造，它的VPTR就已被初始化，
	所以能发生虚函数调用在继承中，如果不把基类的析构函数设置为虚函数，容易出现内存泄漏问题
	如果一个类中有虚函数，该类就要提供一个虚析构函数，即使该析构函数并不一定是该类需要的。
	这可以保证当一个派生类的对象通过基类指针删除时，这个自定义的派生类析构函数会被调用。
*/
	virtual void func1() { cout << "Derived1::func1()" << endl; }
	virtual void d1_func2() { cout << "Derived1::d1_func2()" << endl; }
	virtual void d1_func3(int i) { cout << "Derived1::d1_func3()" << endl; }
	void d1_func4() { 
		//在普通成员函数中调用虚函数，虚机制也不工作
		func1(); //执行结果为：Derived1::func1()
		}
private:
	int d1;
};

class MyDerived2 :public MyBase
{
public:
	MyDerived2(int d) :d2{ d }, MyBase(d) { cout << "Derived2 construct" << endl; }
	//virtual ~MyDerived2() { cout << "Derived2 destruct" << endl; }
	virtual void func1() { cout << "Derived2::func1()" << endl; }
	virtual void d2_func2() { cout << "Derived2::d2_func2()" << endl; }
	virtual void d2_func3() { cout << "Derived2::d2_func3()" << endl; }
	virtual ~MyDerived2() { cout << "Derived2 destruct" << endl; }
private:
	int d2;
};

class MyDerived3 :public MyDerived1
{
public:
	MyDerived3(int d) :d3{ d }, MyDerived1(d) { cout << "Derived3 construct" << endl; }
	virtual void d3_func1() { cout << "Derived3::func1()" << endl; }
	virtual void d1_func2() { cout << "Derived3::d1_func2()" << endl; }
	virtual void d3_func3() { cout << "Derived3::d3_func3()" << endl; }
	virtual void d3_func4() { cout << "Derived3::d3_func4()" << endl; }
	virtual void d3_func5() { cout << "Derived3::d3_func5()" << endl; }
	virtual ~MyDerived3() { cout << "Derived3 destruct" << endl; }
private:
	int d3;
};

//多继承
class MyDerived4 :public MyBase, public MyBase1
{
public:
	MyDerived4(int d4) :MyBase(d4), MyBase1(d4), d4_{ d4 } { cout << "Derived4 constructor" << endl; }
	virtual void func1() { cout << "Derived4::func1()" << endl; }
	virtual void d4_func2() { cout << "Derived4::d2_func2()" << endl; }
	virtual void d4_func3() { cout << "Derived4::d2_func3()" << endl; }
	~MyDerived4() { cout << "Derived4 destructor" << endl; }
private:
	int d4_;
};

void test_derived4()
{
	MyBase* b0_1 = new MyDerived4(10);
	MyBase1* b1_1 = new MyDerived4(12);

	b0_1->func1();//Derived4::func1()
	b0_1->func2();//Base::func2()
	b0_1->func3();//Base::func3()
	//b0_1->d4_fun2();

	b1_1->func1();//Derived4::func1()
	b1_1->func2();//Base::func2()
	b1_1->func3();//Base::func3()
}

typedef void(*func)(void);

class B
{
public:
	B(int i) :i{ i } { 
		func1();
		cout << "B constructor" << endl;
	}

	virtual void func1() { cout << "B::func1()" << endl; }
	virtual void func2() { cout << "B::func2()" << endl; }

	void func3() { 
		func1();
		cout << "B::func3()" << endl; 
	}
	static void func4() { cout << "B::func1()" << endl; }
	virtual ~B() {}
private:
	int i;
	static int j;
};
int B::j = 1;

void test()
{
	MyBase *b = new MyDerived1(1);
	MyDerived1* d = new MyDerived1(1);
	
	b->func1();//输出结果为：MyDerived1::func1()
	cout << "typeinfo is " << typeid(*b).name() << endl;
	d->func1();
	
	delete b;
	delete d;
}

class A {
	A() {}
	~A() {}
};


void main()
{
	//A a;
	test_derived4();
	test();
	size_t m = sizeof(A);
	B b(1);
	MyBase base(1);
	MyDerived1 d1(2);// 单继承
	MyDerived2 d2(3);// 单继承
	MyDerived3 d3(4);//单继承
	MyDerived4 d4(5);// 多继承

	d1.d1_func4();
	cout << "vfptr的地址=" << (int*)&d3 << endl;
	cout << "vftable的地址=" << (int*)*(int*)&d3 << endl;
	cout << "vftable第一个函数的地址=" << (int*)*(int*)*(int*)&d3 << endl;
	cout << "类型信息地址=" << (int*)*(int*)&d3 - 1 << endl;
	for (int i = 0; i < 5; ++i)
	{//不能到第四个索引，因为class derived1的d1_fun3(int)的函数指针类型如此处不符合
		//编译不会报错，但是运行会报错
		func p = (func)*((int*)*(int*)&d1 + i);
		p();
	}
	
	
	system("pause");
}