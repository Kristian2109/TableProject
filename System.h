#pragma once
#include "Table.h"
#include "MyString.h"
#include "Constants.h"

class System
{
	Table* currentTable = nullptr;
	MyString currentFile;
	char userInput[MAX_LEN_COMMAND] = "Nothing";

	void displayOptionsMessage();
	bool open(const MyString& fileName);

	void printOption(const char* optionString) const;
	void printInitialOptions() const;

	void handleTableCommands();
	void handleFormulas();
	void makeFormula(double firstNum, double secondNum, char formulaOperator) const;
	void printResultFormula(double result) const;

	void executeGet(const MyVector<MyString>& inputVector) const;
	void executeEdit(const MyVector<MyString>& inputVector);
	void executeSave(const MyVector<MyString>& inputVector) const;

	bool extractCellReferences(const MyString& value, size_t& row, size_t& col) const;
	double getValueFromInput(const MyString& input) const;
	char getOperatorFromInput(const MyString& input) const;

public:
	System() = default;
	System& operator=(const System& other) = delete;
	System(const System& other) = delete;
	void run();
};