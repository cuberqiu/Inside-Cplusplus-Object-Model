#include<iostream>

using namespace std;

//bitwise copy¡¢memberwise copy¡¢shallow copy¡¢deep copy
class Word
{
public:
	Word(char* str)
	{//default constructor
		cnt_ = strlen(str) + 1;
		str_ = new char[cnt_];
		strcpy(str_, str);
	}
	Word& operator=(const Word& w)
	{//memberwise copy==deep copy
		if (this == &w)//if it is the same object
			return *this;
		delete[] str_;//delete the old memory
		str_ = nullptr;
		str_ = new char[strlen(w.str_) + 1];
		strcpy(str_, w.str_);
		return *this;
	}
	~Word()
	{
		delete[] str_;
	}
public:
	int cnt_;
	char* str_;
};

void test_word()
{
	Word word("abc");   //call the constructor
	Word word1 = word; //default memberwise initialization, 
	//and it`s completed by bitwise copy semantics(shallow copy),it will invoke mistake
	cout << "word.str_=" << (int*)word.str_ << endl;
	cout << "word1.str_=" << (int*)word1.str_ << endl;
	Word word2("def");
	word2 = word;//there will use deep copy if the class Word does not have a expilcit deep copy,
	//or it will be bitwise copy ,and then invoke mistake
	cout << "word.str_=" << (int*)word.str_ << endl;
	cout << "word2.str_=" << (int*)word2.str_ << endl;
}
/*result:
	word.str_=00A73C38
	word1.str_=00A73C38
	word.str_=00A73C38
	word2.str_=00A77758
*/

class Animal
{
public:
	Animal(int cnt) :cnt_{ cnt }
	{
		cout << "default constructor" << endl;
	}
	Animal(const Animal& a)
	{
		this->cnt_ = a.cnt_;
		cout << "copy constructor" << endl;
	}
	Animal& operator=(const Animal& a)
	{
		cout << "copy assignment" << endl;
		this->cnt_ = a.cnt_;
		return *this;
	}
	Animal(Animal&& a)
	{
		cout << "move constructor" << endl;
		this->cnt_ = move(a.cnt_);
	}
	Animal& operator=(Animal&& a)
	{
		cout << "move assignment" << endl;
		this->cnt_ = move(a.cnt_);
		return *this;
	}
public:
	int cnt_;
};

Animal test_animal(Animal a)//call copy constructor
{
	Animal panda(a);//call copy constructor
	Animal dog = panda;//call copy constructor
	return dog;
	//if there is expilcit move constructor ,there will call move constructor, 
	//or it will call explicit copy constructor or default copy constructor
}


void main_copy()
{
	Animal cat(2);  //call default constructor
	Animal dog(1); //call default constructor
	dog = test_animal(cat);
	//if there is explicit move assignment, there will call move assignment,
	//or it will call expilcit copy assignment or default copy assignment

	//test_word();
	system("pause");
}

/*result
	default constructor
	default constructor
	copy constructor
	copy constructor
	copy constructor
	move constructor
	move assignment
*/