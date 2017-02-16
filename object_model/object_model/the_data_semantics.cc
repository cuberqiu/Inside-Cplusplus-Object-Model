//this file discusses the date semantics
#include<iostream>

using namespace std;

class X { virtual void fuc1() {} };
class Y :public virtual X {};
class Z :public virtual X {};
class A :public Y,public Z {};

void test_sizeof()
{
	cout << "sizeof(X)=" << sizeof(X) << endl;
	cout << "sizeof(Y)=" << sizeof(Y) << endl;
	cout << "sizeof(Z)=" << sizeof(Z) << endl;
	cout << "sizeof(A)=" << sizeof(A) << endl;
}
/*result: classX{}    class X{virtual void fuc1(){}}
			sizeof(X)=1   sizeof(X)=4
			sizeof(Y)=4   sizeof(Y)=8
			sizeof(Z)=4   sizeof(Z)=8
			sizeof(A)=8  sizeof(A)=12
*/

void main()
{
	test_sizeof();
	//cout << "bobo" << endl;
}