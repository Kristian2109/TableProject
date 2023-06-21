#pragma once
#include <iostream>
#include "MyVector.h"

class MyString
{
	char* _data;
	size_t _length;

	void copyFrom(const MyString& data);
	void free();

	explicit MyString(size_t capacity); //for memory allocation. How much bytes to allocate
public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	size_t length() const;
	MyString& operator+=(const MyString& other);

	MyString substr(size_t begin, size_t howMany) const;
	void setValue(const char* value);
	int find(char symbol) const;
	void findAll(char symbol, int* indexes) const;
	void addChar(char symbol);
	void add(char symbol, size_t position);
	void remove(size_t index);
	void append(const MyString& other);

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;
	bool isEmpty() const;
	bool contains(char symbol) const;

	bool operator<(const MyString& rhs) const;
	bool operator<=(const MyString& rhs) const;
	bool operator>=(const MyString& rhs) const;
	bool operator>(const MyString& rhs) const;
	bool operator==(const MyString& rhs) const;
	bool operator!=(const MyString& rhs) const;

	MyVector<MyString> split(char symbol) const;

	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend const MyString& operator>>(const MyString& str, int& number);
	friend MyString& operator<<(MyString& str, double& number);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);
const MyString& operator>>(const MyString& str, int& number);
MyString& operator<<(MyString& str, double& number);

