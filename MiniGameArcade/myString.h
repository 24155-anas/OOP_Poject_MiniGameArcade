#ifndef MYSTRING_H
#define MYSTRING_H
#include<iostream>
using namespace std;

class myString {
private:
	char* str;
	int l;
	int cap;

	//length calculator
	int length(const char* _str);
public:
	//default constructor
	myString();

	//parametrized contructors
	myString(char ch);   //myString s2('A') will create "A" 
	myString(const char* _str);  //myString s3("hello");  se "hello" bane ga
	myString(char ch, int size);  //myString s1('a',5) se "aaaaa" banega
	myString(int size);

	//copy contructor
	myString(const myString& _str);

	//display function
	void display();

	//shallow copy
	void replace_first(char ch);

	void trim();

	//integer to string
	myString itos(int num);

	//string to integer
	int stoi(const char* _str);

	//=====equality functions=====
	bool isEqual(const myString& s2);
	//overloading the same func
	bool operator==(const myString& s2);

	bool isNotEqual(const myString& s2);
	//overloading the same func
	bool operator!=(const myString& s2);

	bool isLesser(const myString& s2);
	//overloading it
	bool operator<(const myString& s2);

	bool isGreater(const myString& s2);
	//overloading it
	bool operator>(const myString& s2);

	//====find funcs===
	int find_first(char ch);
	int find_first(const myString& s2);
	int find_last(char ch);
	int find_last(const myString& s2);
	int* find_all(char ch, int& C);
	int* find_all(const myString& s2, int& C);

	//====remove funcs=====
	void remove_at(int idx);
	void remove_first(char ch);
	void remove_last(char ch);
	void remove_all(char ch);

	//=====insert funcs=====
	void insert_at(int idx, char ch);// Add a character at given position
	void insert_at(int idx, const myString& s2);// Add a string at given position

	//==== upper / lower funcs ====
	void to_upper();
	void to_lower();

	//==split func===
	myString* split(char delim, int& count);

	//==tokenize==
	myString* tokenize(const char* delimiter, int& count);

	//concat , append
	myString concat(const myString& s2);
	//overloading it
	myString operator+(const myString& s2);

	void append(const myString& s2);

	//==all substr search==
	int* all_sub_search(const char* substr, int& C);

	char operator[](int i) const;
	char& operator[](int i);
	myString& operator=(const myString& other);

	void clear();
	friend ostream& operator<<(ostream& os, const myString& obj);
	friend istream& operator>>(istream& is, myString& obj);
	~myString();
};

#endif