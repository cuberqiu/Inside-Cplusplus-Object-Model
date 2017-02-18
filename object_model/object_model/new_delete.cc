//new和delete

/*
	new和delete的机制：
	new和delete都不是函数，是C++中的关键字
	当用new创建一个对象时，它就在堆里为对象分配内存，然后为这块内存调用构造函数，
	并返回一个指向new运算符右边类型的指针。
	当用delete释放一个对象时，首先调用析构函数，然后释放内存；注意：delete表达式需要
	一个对象的地址。
	new运算符表达式是C++的一种语言结构，不可重载。但用户可重载operator new()函数。

	参考博客：http://www.cnblogs.com/hazir/p/new_and_delete.html
*/

#include<iostream>

using namespace std;

class Time {
public:
	Time(int h, int m, int s);
	~Time();
private:
	int hour;
	int min;
	int sec;
	char *name;
};

Time::Time(int h, int m, int s) :hour{ h }, min{ m }, sec{ s } {
	name = new  char[h];
	cout << "Construct object " << endl;
	cout << "Time is " << hour << ":" << min << ":" << sec << endl;
}

Time::~Time()
{
	delete[] name;
	cout << "Destructing object" << endl;
}

void main6()
{
	Time *p1 = new Time(1, 2, 3);
	delete p1;   //delete p1，知道p1是一个Time对象，所以会调用析构函数
	void *p2 = new Time(3, 2, 1);       //delete会导致内存泄漏
	delete p2;   //delete p2， 但是不知道p2的类型，只会释放p2对象的内存，但是不会调用析构函数
	//注：若使用void*，在删除它之前一定要将其转换成适当类型进行释放
	void* p3 = new Time(2, 3, 4);
	delete (Time*)p3;

	int *p4 = new int(14);
	cout << *p4 << endl;
	delete p4;
}