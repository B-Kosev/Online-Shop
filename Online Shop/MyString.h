#pragma once
#include <iostream>

//using namespace std;

class String 
{
	char* content;
	int sizeVal;
public:
	String();
	String(const char* input);
	String(const String& from);

	String& operator=(const String& from);


	~String();

	//iterators

	//capacity
	int size() const;

	//access
	char& operator[] (int);

	//modifiers
	void push_back(char to_append);
	void pop_back();
	void append(const String& toAppend);

	void clear();
	int find(const String& str) const;


	void print() const;

	friend std::ostream& operator<<(std::ostream& out,const String& obj);
	friend std::istream& operator>>(std::istream& in,String& obj);
	friend std::istream& getline(std::istream& in, String& obj);

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, const String& rhs);
};