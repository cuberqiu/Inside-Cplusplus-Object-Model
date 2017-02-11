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
	Object12(int i) :i_{ i } { cout << "���캯��" << endl; }
	Object12(const Object12& O)
	{
		cout << "�������캯��" << endl;
		this->i_ = O.i_;
	}
	Object12(Object12&& o) :i_{o.i_}
	{
		cout << "�ƶ����캯��" << endl;
	}
	Object12& operator=(Object12&& o)
	{
		i_ = move(o.i_);
		cout << "�ƶ���ֵ" << endl;
		return *this;
	}
	Object12& operator=(const Object12& o)
	{
		i_ = o.i_;
		cout << "������ֵ" << endl;
		return *this;
	}
public:
	int i_;
};

Object12 foo()
{
	Object12 o(2);
	return o; //return ���õ����ƶ����캯��
}
void main()
{
	Object12 o1(1);
	Object12 o2 = o1;//���ÿ������캯��
	Object12 o3(o1);
	o2 = o1;
	o3 = foo();  //
	//cout << o1.i << endl;  //�ᱨ������Ϊiû�б���ʼ����Ĭ�Ϲ��캯��������ʼ����Щ����
	int array[] = { 1,2,3 };
	char str[] = { 'a','b','c' ,'\0'}; //����������ʱ����'\0'����cout����
	char str1[] = "abc";  //Ĭ����'\0'
	cout << array << endl;  //�������鲻����������
	cout << "str="<< str << endl;
	cout << "str1=" << str1 << endl;
	Object O1(1);
	cout << "sizeof(Object)=" << sizeof(Object) << endl;
	cout << "sizeof(O1)=" << sizeof(O1) << endl;
	cout << "sizeof(x)=" << sizeof(x) << endl;
}