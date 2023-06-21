#include <iostream>
#include "StringFunctions.h"
#include "Constants.h"

bool isLetter(char symbol)
{
	return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}

void print(const char* str)
{
	std::cout << str;
}

void printMessage(const char* message)
{
	print(message);
	system("pause");
	system("CLS");
}

void printSymbol(char symbol, unsigned times)
{
	for (size_t i = 0; i < times; i++)
	{
		std::cout << symbol;
	}
}

bool isString(const char* value)
{
	if (value == nullptr || value[0] == '\0') { return false; }
	size_t index = 0;

	while (value[index] != '\0')
	{
		if (!isLetter(value[index]) && !STRING_SYMBOLS.contains(value[index])) { return false; }
		index++;
	}

	return true;
}

void castEnd(char* str, unsigned lenStr)
{
	for (size_t i = lenStr - 1; i > 0; i--)
	{
		if (str[i] != ' ')
		{
			break;
		}
		str[i] = '\0';
	}
}


void castBegin(char* str, unsigned lenStr)
{
	unsigned indexOfFirstChar = 0;
	for (size_t i = 0; i < lenStr; i++)
	{
		if (str[i] != ' ')
		{
			break;
		}
		indexOfFirstChar++;
	}

	for (size_t i = 0; i < lenStr; i++)
	{
		str[i] = str[i + indexOfFirstChar];
	}

	str[lenStr - indexOfFirstChar] = '\0';
}

MyString getCastedString(char* str)
{
	if (str[0] == '\0') { return MyString(""); }

	int lenStr = strlen(str);
	castEnd(str, lenStr);

	lenStr = strlen(str);
	castBegin(str, lenStr);

	MyString value(str);

	if (str[0] == '"')
	{
		value.remove(0);
		value.remove(value.length() - 1);
	}

	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[i] == '\\')
		{
			value.remove(i);
			if (value[i + 1] == '\\') { i++; }
		}
	}

	return value;
}

bool isDigit(char symbol)
{
	return symbol >= 48 && symbol <= 57;
}

bool isValidIndex(const MyString& string)
{
	if (string.isEmpty()) { return false; }
	for (size_t i = 0; i < string.length(); i++)
	{
		if (!isDigit(string[i])) { return false; }
	}

	return true;
}

bool isValidDouble(const char* str) {
	if (str == nullptr || str[0] == '\0') {
		return false;
	}

	if (str[0] == '+' || str[0] == '-') {
		++str;
	}

	bool hasDecimal = false;
	bool hasDigits = false;

	while (*str != '\0') {
		if (*str == '.') {
			if (hasDecimal) {
				return false;// Multiple decimal points found
			}
			hasDecimal = true;
		}
		else if (*str < '0' || *str > '9') {
			return false;
		}
		else {
			hasDigits = true;
		}

		++str;
	}

	return hasDigits;
}

double convertStringToDouble(const char* str) {

	double result = 0.0;
	double decimal = 0.1;
	bool isNegative = false;
	bool hasDecimal = false;

	if (str == nullptr || str[0] == '\0') {
		return result;
	}

	if (str[0] == '-') {
		isNegative = true;
		++str; // Move the pointer past the negative sign
	}
	else if (str[0] == '+') { str++; };

	while (*str != '\0') {
		if (*str == '.') {
			hasDecimal = true;
			++str; // Move the pointer past the decimal point
			continue;
		}

		if (*str < '0' || *str > '9') {
			throw std::invalid_argument("The string isn't valid number!");
		}

		if (!hasDecimal) {
			result = result * 10.0 + (*str - '0');
		}
		else {
			result += (*str - '0') * decimal;
			decimal *= 0.1;
		}

		++str; // Move the pointer to the next character
	}

	if (isNegative) {
		result = -result;
	}

	return result;
}

bool isKnownValueType(const MyString& value)
{
	return value.length() == 0 || isString(value.c_str()) || isValidDouble(value.c_str());
}

MyString getFormatedStringForSaving(const MyString& value)
{
	MyString result = value;

	for (size_t i = 0; i < result.length(); i++)
	{
		if (result[i] == '"' || result[i] == '\\')
		{
			result.add('\\', i++);
		}
	}

	return result;
}
