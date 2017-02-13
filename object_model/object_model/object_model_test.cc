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

void main()
{
	cout << "HeartCraft" << endl;
}