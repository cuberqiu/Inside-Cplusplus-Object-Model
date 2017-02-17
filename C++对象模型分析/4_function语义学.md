# **function语义学**

> _**Author:邱雨波**_
>
> _**2017年2月17日更新**_

> 本节讨论函数语义问题  
> 参考程序：[function_semantics.cc](https://github.com/CraftHeart/Inside-Cplusplus-Object-Model/blob/Inside-The-C%2B%2B-Object-Model/object_model/object_model/function_semantics.cc)
## **1 Member Function Calling Mechnism**

### **1.1 Nonstatic Member Functions**

C++的设计准则之一就是：nonstatic member function至少必须和一般的nonmember function相同的效率。也就是说，如果我们要在以下两个函数之间作选择：

```c++
void func(){};
void A::func(){};
```

那么选择member function不应该带来什么额外负担。这是因为编译器内部将“member函数实体”转换成对等的“nonmember函数实体”。

类的成员函数，对于类来讲，一方面**逻辑上属于类**，另一方面**物理上不属于类**。  

类的成员变量，nonstatic member data是类的一部分，也是对象的一部分，staticmember data是类的一部分，不是对象的一部分。

nonstatic member fucntion可以调用类的nonstatic member data和static member data。nonstatic member function 存在于代码区，通过this指针调用nonstatic member data。当调用一个nonstatic member function时，会传入一个object对象的this指针。例如，float X::func(){}===>float func(X* this){}。

C++的设计准则之一就是：nonstatic member function至少必须和一般的nonmember function有相同的效率。因此，在编译器内部，会将类的成员函数转换成等价的非成员函数，转化步骤如下：

1. 改写函数的原型以安插一个额外的参数到member functio中，用以提供一个存取管道，使class object得以调用该函数。该额外参数被称为this指针。

   ```c++
   //nonconst nonstatic member
   class Point{
     public:
     void func1(){x_=1;}
     void func2()const{cout<<x_<<endl;}
     private:
     int x_,y_;
   }
   //in the compiler,func1 and func2 will like as follow
   Point::func1(Point *const this){this->x_=1;}
   Point::func2(const Point *const this){cout<<this->x_<<endl;}
   ```

2. 将每一个“对nonstatic data member的存取操作”改为经由this指针来存取。

   ```c++
   //in the compiler,func1 and func2 will like as follow
   Point::func1(Point *const this){this->x_=1;}
   Point::func2(const Point *const this){cout<<this->x_<<endl;}
   ```

3. 将member function重新写成一个外部函数。对函数名称进行“mangling”处理，使它称为程序中独一无二的词汇。

   ```c++
   extern func1_Point(register Point*const this);
   ```

### **1.2 Virtual Member Function**

如果func()是Point类的第一个virtual member function，那么下面的调用：

```c++
Point* ptr = new Point;
ptr->func();
```

将会被转化为：

```c++
(*ptr->vptr[0])(ptr);
```

- vptr是由编译器为类对象object产生的虚指针，指向virtual table。
- 0表示virtual table slot的索引值，在0索引处存放着func()函数的地址。
- 第二个ptr表示this指针。

### **1.3 Static Member Fucntion**

如果func1()是Point类的一个static member function，那么下面的调用：

```c++
Point* ptr = new Point;
ptr->func1();
```

将会被转化为：

```c++
func1_Point();
```

static member function的主要特性就是它没有this指针。以下的次要特性统统根源于其主要特性：

- 它不能够直接存取其class中的nonstatic members；
- 它不能够被声明为const、volatile或virtual。
- 它不需要经由class object就可以调用。

## **2 Pointer-to-Member Function**

定义一个类：

```c++
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
```

nonstatic member function 函数指针的定义和使用如下：

```c++
typedef Return_Type (Class X::* pointer_name)(Argument_Type argument_name);

//definition
typedef void (Student::*ptr_nonstatic_func)();//nonstatic member function pointer definition

//using
Student s1(1);
ptr_nonstatic_func ptr_nonstatic = &Student::nonstatic_func1;
(s1.*ptr_nonstatic)();//using nonstatic member function pointer need an object;
```

static member fuction函数指针的定义和使用如下：

```c++
typedef Return_Type (* pointer_name)(Argument_Type argument_name);  //no this pointer

//definition
typedef void(*ptr_static_func)();//static member function pointer definition

//using
Student s1(1);
ptr_static_func ptr_static = &Student::static_func2;
ptr_static();//using static member function do not need an object 
```

virtual member function函数指针的定义和使用如下：

```c++
typedef Return_Type (Class X::* pointer_name)(Argument_Type argument_name);

//definition
typedef void (Student::*ptr_virtual_func)();//virtual member function pointer definition

//using 
Student s1(1);
ptr_virtual_func ptr_virtual = &Student::virtual_func1;
(s1.*ptr_virtual)();
```

在单继承中的pointer-to-member function，定义和使用如下：

```c++
//member function pointer in inherent，virtual mechnism is valid
void (BaseStudent::* pbase)() = &BaseStudent::virtual_func1;
BaseStudent* p_to_d = new Student(1);
p_to_d->virtual_func1();
(p_to_d->*pbase)();
/*result:
  Student::virtual func1()
  Student::virtual func1()
*/
```
