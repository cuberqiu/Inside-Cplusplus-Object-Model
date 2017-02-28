#include<iostream>

using namespace std;

class RunTime
{
public:
	
public:
	int hour_;
	int minute_;
	int second_;
	char *ptr_;
};

//all the global objects will be set at data segment,
//if explicitly initializing it with a value,this value will be it`s initial value,
//or the data member of global objects will be set as 0.
int g_i;  //g_i=0
char* g_ptr; //(int*)g_ptr = 0
RunTime g_run_time; //data member of g_run_time will be initailized with 0 

void test_runtime()
{
	int local_i;  //no initialization, the value is uncertainty
	char* ptr;   //no initialization, the value is uncertainty
	RunTime run_time;   //no explicit constructor, the class data member value is uncertainty


	cout << "g_i=" << g_i << endl;   //g_i = 0
    //cout << "local_i=" << local_i << endl;   //runtime error: local_i hasn`t initialized

	cout << "g_ptr = " << (int*)g_ptr << endl;
	cout << "ptr= " << (int*)ptr << endl;

	cout << "g_run_time.hour_ = " << g_run_time.hour_ << endl;   //g_run_time.hour_ = 0;
    //cout << "run_time.hour_ = " << run_time.hour_ << endl;  //runtime error: run_time hasn`t initialized
	cout << "g_run_time.ptr_ = " << (int*)g_run_time.ptr_ << endl;
	cout << "run_time.ptr_ = " << (int*)run_time.ptr_ << endl;//runtime error: run_time hasn`t initialized
}

//array of class
class ArrayClass
{//has explicit constructor
public:
	int cnt_;
public:
	ArrayClass(int cnt =0) :cnt_{ cnt } {}
};
class ArrayClass1
{//no explicit constructor
public:
	int cnt_;
public:
	//ArrayClass(int cnt) :cnt_{ cnt } {}
};

//if ArrayClass has explicit cosnturctor, it`s member data only can be initialized by constructor
ArrayClass g_arrayclass[10];  //complier error: no suitable constructor
ArrayClass1 g_arrayclass1[10];

void test_arrayclass()
{
	cout << "g_arrayclass[0].cnt_=" << g_arrayclass[0].cnt_ << endl; //compiler error .cnt_ hasn`t been initialized
	cout << "g_arrayclass1[0].cnt_=" << g_arrayclass1[0].cnt_ << endl; //=0
}

void main_runtime()
{
	//test_runtime();
	test_arrayclass();
}