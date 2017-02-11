#include<iostream>
using namespace std;


class Object
{
public:
	Object(int a) :a{ a } {}
	~Object() {}
	void func1() {}
private:
	int a;
	static int b;
};
int Object::b = 1;
static int x = 1;

class Object12
{
public:
	Object12(int i) :i_{ i } { cout << "构造函数" << endl; }
	Object12(const Object12& O)
	{
		cout << "拷贝构造函数" << endl;
		this->i_ = O.i_;
	}
	Object12(Object12&& o) :i_{o.i_}
	{
		cout << "移动构造函数" << endl;
	}
	Object12& operator=(Object12&& o)
	{
		i_ = move(o.i_);
		cout << "移动赋值" << endl;
		return *this;
	}
	Object12& operator=(const Object12& o)
	{
		i_ = o.i_;
		cout << "拷贝赋值" << endl;
		return *this;
	}
public:
	int i_;
};

Object12 foo()
{
	Object12 o(2);
	return o; //return 调用的是移动构造函数
}
void main()
{
	Object12 o1(1);
	Object12 o2 = o1;//调用拷贝构造函数
	Object12 o3(o1);
	o2 = o1;
	o3 = foo();  //
	//cout << o1.i << endl;  //会报错，因为i没有被初始化，默认构造函数不会初始化这些东西
	int array[] = { 1,2,3 };
	char str[] = { 'a','b','c' ,'\0'}; //若这样定义时不加'\0'，将cout乱码
	char str1[] = "abc";  //默认有'\0'
	cout << array << endl;  //整型数组不能这样输出
	cout << "str="<< str << endl;
	cout << "str1=" << str1 << endl;
	Object O1(1);
	cout << "sizeof(Object)=" << sizeof(Object) << endl;
	cout << "sizeof(O1)=" << sizeof(O1) << endl;
	cout << "sizeof(x)=" << sizeof(x) << endl;
}