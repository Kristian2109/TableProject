#pragma once
#include "MyString.h"

const char LEFT_PADDING = 5;
const size_t MAX_LEN_COMMAND = 1024;
const MyString OPERATORS = "+-*/^";
const MyString STRING_SYMBOLS = "?.,!:-_;&'\\\"0123456789 ";

namespace commands
{
	const char DEFAULT[] = "nothing";
	const char EXIT[] = "exit";
	const char CLOSE[] = "close";
	const char PRINT[] = "print";
	const char SAVE[] = "save";
	const char EDIT[] = "edit";
	const char FORMULAS[] = "formulas";
	const char GET[] = "get";
	const char OPEN[] = "open";
}

namespace messages
{
	const char FAIL_LOAD[] = "Error while loading the file! Try again\n";
	const char FAIL_SAVE[] = "Error whit the file while saving!\n";
	const char SUCCESS_SAVE[] = "Table saved successfully!\n";
	const char CLOSE[] = "Table closed successfully!\n";
	const char INVALID_COMMAND[] = "Invalid command. Try again!\n";
	const char INVALID_ROW[] = "Invalid index for row!\n";
	const char INVALID_COL[] = "Invalid index for col!\n";
	const char INVALID_INDEX[] = "Invalid index!\n";
	const char INVALID_FORMAT[] = "Wrong format!\n";
	const char DIVISION_ZERO[] = "Erorr: division by zero!\n";
	const char SUCCESS_OPEN[] = "File opened successfully!\n";
	const char POW_ERROR[] = "Invalid power. Power should be whole a number!\n";
}

