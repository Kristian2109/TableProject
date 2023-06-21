#pragma once
#include "MyString.h"


bool isString(const char* value);

bool isLetter(char symbol);

void printMessage(const char* message);

bool isValidIndex(const MyString& string);

double convertStringToDouble(const char* str);

bool isValidDouble(const char* str);

void printSymbol(char symbol, unsigned times);

void castEnd(char* str, unsigned lenStr);

void castBegin(char* str, unsigned lenStr);

MyString getCastedString(char* str);

bool isWholeNumber(double number);

void print(const char* str);

bool isKnownValueType(const MyString& value);

MyString getFormatedStringForSaving(const MyString& value);