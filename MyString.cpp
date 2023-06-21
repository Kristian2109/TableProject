#include "MyString.h"
#pragma warning(disable : 4996)
#include <sstream>

MyString::MyString(size_t capacity)
{
	_length = capacity - 1;
	_data = new char[capacity];
}

void MyString::setValue(const char* value)
{
	free();
	_length = strlen(value);
	_data = new char[_length + 1];
	strcpy(_data, value);
}

int MyString::find(char symbol) const
{
	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] == symbol) { return i; }
	}

	return -1;
}

void MyString::append(const MyString& other)
{
	_length = _length + other.length();
	char* newData = new char[_length + 1];
	newData[0] = '\0';

	strcat(newData, _data);
	strcat(newData, other._data);

	delete _data;
	_data = newData;
}

void MyString::remove(size_t index)
{
	if (index >= _length)
	{
		throw std::out_of_range("Index out of range!");
	}

	for (size_t i = index; i < _length; i++)
	{
		_data[i] = _data[i + 1];
	}

	_data[--_length] = '\0';
}

void MyString::findAll(char symbol, int* indexes) const
{
	size_t indexOfIndex = 0;

	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] == symbol)
		{
			indexes[indexOfIndex++] = i;
		}
	}

	indexes[indexOfIndex] = -1;

}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs._length + rhs._length + 1);

	result[0] = '\0';
	strcat(result._data, lhs._data);
	strcat(result._data, rhs._data);

	return result;
}

MyString& MyString::operator+=(const MyString& other)
{
	char* result = new char[(_length += other._length) + 1];
	result[0] = '\0';
	strcat(result, _data);
	strcat(result, other._data);

	delete[] _data;
	_data = result;

	return *this;
}

MyString::MyString() : MyString(1)
{
	_data[0] = '\0';
}

MyString::MyString(const char* data) : MyString(strlen(data) + 1)
{
	strcpy(_data, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


void MyString::free()
{
	delete[] _data;
	_data = nullptr;
}

MyString::~MyString()
{
	free();
}

size_t MyString::length() const
{
	return _length;
}

bool MyString::contains(char symbol) const
{
	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] == symbol) { return true; }
	}

	return false;
}

void MyString::copyFrom(const MyString& other)
{
	_length = other._length;
	_data = new char[_length + 1];
	strcpy(_data, other._data);
}

MyString::MyString(MyString&& other) noexcept
{
	_data = other._data; // to function moveFrom ?
	other._data = nullptr;
	_length = other._length;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		_data = other._data;
		other._data = nullptr;
		_length = other._length;
	}
	return *this;
}

char& MyString::operator[](size_t index) //Неконстантен достъп
{
	return _data[index];
}

char MyString::operator[](size_t index) const //Константен достъп 
{
	return _data[index];
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > _length)
		throw std::length_error("Error, Substr out of range");


	MyString res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res._data[i] = _data[begin + i];
	res[howMany] = '\0';
	return res;
}

const char* MyString::c_str() const
{
	return _data;
}

bool MyString::isEmpty() const
{
	return _length == 0;
}

void MyString::addChar(char symbol)
{
	char* newData = new char[++_length + 1];
	newData[0] = '\0';
	strcat(newData, _data);
	newData[(_length - 1)] = symbol;
	newData[_length] = '\0';

	delete[] _data;
	_data = newData;
}

void MyString::add(char symbol, size_t position)
{
	char* newData = new char[_length + 2];
	
	for (size_t i = 0; i < position; i++)
	{
		newData[i] = _data[i];
	}

	newData[position] = symbol;

	for (size_t i = position; i < _length; i++)
	{
		newData[i + 1] = _data[i];
	}

	newData[++_length] = '\0';

	delete[] _data;
	_data = newData;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff; // is.getLine(buff, 1024);

	delete[] str._data;
	str._length = strlen(buff);
	str._data = new char[str._length + 1];
	strcpy(str._data, buff);
	return is;
}

const MyString& operator>>(const MyString& str, int& number)
{
	std::stringstream ss;
	ss << str;

	ss >> number;
	return str;
}

MyString& operator<<(MyString& str, double& number)
{
	std::stringstream stream;

	stream << number;

	stream >> str;

	return str;
}

bool MyString::operator<(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) < 0;
}

bool MyString::operator<=(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) <= 0;
}
bool MyString::operator>=(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) >= 0;
}
bool MyString::operator>(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) > 0;
}
bool MyString::operator==(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) == 0;
}
bool MyString::operator!=(const MyString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) != 0;
}

MyVector<MyString> MyString::split(char symbol) const
{
	MyVector<MyString> pieses;
	pieses.push_back();
	size_t pieceIndex = 0;
	pieses[pieceIndex].addChar(_data[0]);

	for (size_t i = 1; i < length(); i++)
	{
		if (_data[i] == symbol && _data[i - 1] != symbol)
		{
			pieses.push_back();
			pieceIndex++;
			continue;
		} 
		else if (_data[i] != symbol)
			pieses[pieceIndex].addChar(_data[i]);
	}

	return pieses;
}
