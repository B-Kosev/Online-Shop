#include "MyString.h"
#include <cstring>
#include <iostream>

#pragma warning(disable:4996)

//using namespace std;

String::String()
{
	content = new char[1];
	content[0] = '\0';
	sizeVal = 0;
}

String::String(const char* input)
{
	int len = strlen(input);
	this->content = new char[len + 1];

	strcpy(this->content, input);
	this->content[len] = '\0';
	sizeVal = strlen(content);
}
String::String(const String& from)
{
	int len = strlen(from.content);
	this->content = new char[len + 1];
	strcpy(this->content, from.content);
	this->content[len] = '\0';
	sizeVal = strlen(content);
}

String& String::operator=(const String& from)
{
	if (this != &from)
	{
	    delete[] content;

		int len = strlen(from.content);
		this->content = new char[len + 1];
		strcpy(this->content, from.content);
		this->content[len] = '\0';
		sizeVal = strlen(content);
	}
	return *this;
}

String::~String()
{
	delete[] this->content;
}

int String::size() const
{
	return sizeVal;
}

char& String::operator[](int pos)
{
	if (pos >= 0 && pos < size()) return content[pos];
}

void String::push_back(char to_append)
{
	int len = strlen(this->content);
	char* new_content = new char[len + 2];
	strcpy(new_content, this->content);
	new_content[len] = to_append;
	new_content[len + 1] = '\0';
	delete[] this->content;
	this->content = new_content;
	sizeVal = strlen(content);
}

void String::pop_back()
{
	char* newContent = new char[strlen(content)];
	for (int i = 0;i < strlen(content)-1;i++)
	{
		newContent[i] = content[i];
	}
	newContent[strlen(content) - 1] = '\0';
	delete[] content;
	content = newContent;
	sizeVal = strlen(content);
}

void String::append(const String& toAppend)
{
	char* newContent = new char[sizeVal + toAppend.sizeVal+1];
	strcpy(newContent, content);
	strcat(newContent, toAppend.content);
	delete[] content;
	content = newContent;
	sizeVal = strlen(content);
}

void String::clear()
{
	delete[] content;
	char* newContent = new char[1];
	newContent[0] = '\0';
	content = newContent;
	sizeVal = 0;
}

int String::find(const String& str) const
{
	int ind = -1;
	bool flag = false;
	for (int i = 0;i < sizeVal;i++)
	{
		if (content[i] == str.content[0]) //match first symbol of str with this
		{
			ind = i;
			//check the remaining symbols from str
			for (int j = 1;j < str.size();j++)
			{
				if (content[j + i] == str.content[j])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag) //str is in this
			{
				return ind;
			}
			else ind = -1;
		}
	}
	return ind;
}

void String::print() const
{
	std::cout << this->content;
}

std::ostream& operator<<(std::ostream& out, const String& obj)
{
	out << obj.content;
	return out;
}

std::istream& operator>>(std::istream& in, String& obj)
{
	char toAppend=0;
	toAppend = in.get();
	if (toAppend > ' ') 
	{
		obj.push_back(toAppend);
		while (in.get(toAppend) && toAppend != '\n' && toAppend != '\t' && toAppend != ' ') obj.push_back(toAppend);
	}
	else //custom ignore()
	{
		toAppend = 0;
		while (in.get(toAppend) && toAppend != '\n' && toAppend != '\t' && toAppend != ' ') obj.push_back(toAppend);
	}
	return in;
}

std::istream& getline(std::istream& in, String& obj)
{
	char toAppend = 0;
	toAppend = in.get();
	while (in.get(toAppend) && toAppend != '\n') obj.push_back(toAppend);
	return in;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (strcmp(rhs.content, lhs.content) == 0) return true;
	return false;
}

bool operator!=(const String& lhs, const String& rhs)
{
	if (strcmp(rhs.content, lhs.content) == 0) return false;
	return true;
}

bool operator>(const String& lhs, const String& rhs)
{
	int rhsLen = strlen(rhs.content), lhsLen = strlen(lhs.content);
	if (lhsLen > rhsLen) return true; //lhs is longer than rhs
	if (lhsLen < rhsLen) return false; //lhs is shorter than rhs

	//same lenght
	for (int i = 0;i < rhsLen;i++)
	{
		if (lhs.content[i] > rhs.content[i]) return true;
		if (lhs.content[i] < rhs.content[i]) return false;
	}
	//strings are equal
	return false;
}

bool operator<(const String& lhs, const String& rhs)
{
	int rhsLen = strlen(rhs.content), lhsLen = strlen(lhs.content);
	if (lhsLen > rhsLen) return false; //lhs is longer than rhs
	if (lhsLen < rhsLen) return true; //lhs is shorter than rhs

	//same lenght
	for (int i = 0;i < rhsLen;i++)
	{
		if (lhs.content[i] > rhs.content[i]) return false;
		if (lhs.content[i] < rhs.content[i]) return true;
	}
	//strings are equal
	return false;
}

String operator+(const String& lhs, const String& rhs)
{
	String res(lhs);
	res.append(rhs);
	return res;
}