#include "System.h"
#include "StringFunctions.h"
#include "NumberFunctions.h"
#include "Constants.h"
#include <sstream>

void System::run()
{
	while (true)
	{
		printInitialOptions();
		std::cin.getline(userInput, MAX_LEN_COMMAND);
		MyString input = MyString(userInput);
		MyVector<MyString> userWords = input.split(' ');

		if (userWords[0] == commands::EXIT) { break; }

		if (userWords[0] == commands::OPEN)
		{
			if (userWords.getSize() < 2 || !open(userWords[1]))
			{
				printMessage(messages::FAIL_LOAD);
				continue;
			}

			printMessage(messages::SUCCESS_OPEN);
			handleTableCommands();
		}
		else 
		{
			printMessage(messages::INVALID_COMMAND);
		}

		delete currentTable;
		currentTable = nullptr;
	}
	
}

void System::handleTableCommands()
{
	while (true)
	{
		displayOptionsMessage();

		std::cout << "Enter your command: ";
		std::cin.getline(userInput, MAX_LEN_COMMAND);

		MyVector<MyString> userWords = MyString(userInput).split(' ');

		if (userWords[0] == commands::CLOSE)
		{
			printMessage(messages::CLOSE);
			break;
		}
		else if (userWords[0] == commands::SAVE)
		{
			executeSave(userWords);
		}
		else if (userWords[0] == commands::GET)
		{
			executeGet(userWords);
		}
		else if (userWords[0] == commands::EDIT)
		{
			executeEdit(userWords);
		}
		else if (userWords[0] == commands::FORMULAS)
		{
			handleFormulas();
		}
		else if (userWords[0] == commands::PRINT)
		{
			system("CLS");
			currentTable->print();
		}
		else
		{
			printMessage(messages::INVALID_COMMAND);
		}
	}
}

void System::printOption(const char* optionString) const
{
	printSymbol(' ', LEFT_PADDING);
	print("- ");
	print(optionString);
	print("\n");
}

void System::printInitialOptions() const
{
	print("Choose one from the following options.\n");
	printOption("exit");
	printOption("open <fileName>");
}

void System::displayOptionsMessage()
{
	print("Type one from the folloing options: \n");
	printOption("print");
	printOption("close - to close the opened file.");
	printOption("save - to save the file in initial location.");
	printOption("get <row> <column>");
	printOption("edit <row> <column> <value>");
	printOption("save as <filename>");
	printOption("formulas - to open the tab with formulas");
}

bool System::extractCellReferences(const MyString& value, size_t& row, size_t& col) const
{
	if (value[0] != 'R') { return false; }

	std::stringstream ss;
	ss << value;

	ss.seekg(1, std::ios::cur);

	ss >> row;

	if (row == 0 || ss.fail() || ss.get() != 'C') { return false; }

	ss >> col;

	if (col == 0 || ss.fail()) { return false; }

	return ss.eof();
}

void System::executeGet(const MyVector<MyString>& inputVector) const
{
	int row, col;
	if (!isValidIndex(inputVector[1]) || !isValidIndex(inputVector[2]))
	{
		printMessage(messages::INVALID_INDEX);
		return;
	}

	inputVector[1] >> row;
	inputVector[2] >> col;

	try
	{
		MyString value = currentTable->getValue(row - 1, col - 1);
		std::cout << "The value on " << row << " row and " << col << " col is " << value << '\n';
		system("pause"); system("CLS");
	}
	catch (const std::out_of_range& exc)
	{
		printMessage(exc.what());
	}

}

void System::executeEdit(const MyVector<MyString>& inputVector)
{
	int row, col;
	if (!isValidIndex(inputVector[1]) || !isValidIndex(inputVector[2]))
	{
		printMessage(messages::INVALID_INDEX);
		return;
	}

	inputVector[1] >> row;
	inputVector[2] >> col;
	MyString value = "";
	for (size_t i = 3; i < inputVector.getSize(); i++)
	{
		value.append(inputVector[i]);
		if (i != inputVector.getSize() - 1) { value.append(" "); }
	}

	try
	{
		currentTable->setValue(row - 1, col - 1, value);
		std::cout << "The value on " << row << " row and " << col << " col is " << value << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << "Error on row " << row << " and col " << col << std::endl;
		printMessage(exc.what());
	}
}

void System::executeSave(const MyVector<MyString>& inputVector) const
{
	if (inputVector.getSize() == 1)
		currentTable->saveToFile(currentFile.c_str());

	else if (inputVector.getSize() != 3 && inputVector[1] != "as")
		printMessage(messages::INVALID_FORMAT);

	else if (!currentTable->saveToFile(inputVector[2].c_str()))
	{
		printMessage(messages::FAIL_SAVE);
		return;
	}

	printMessage(messages::SUCCESS_SAVE);
}

double System::getValueFromInput(const MyString& input) const
{
	double result = 0;

	if (isValidDouble(input.c_str()))
	{
		result = convertStringToDouble(input.c_str());
	}
	else
	{
		size_t row = 0, col = 0;

		bool isCellReference = extractCellReferences(input, row, col);

		try
		{
			MyString value = currentTable->getValue(row - 1, col - 1);

			if (isValidDouble(value.c_str()))
			{
				result = convertStringToDouble(value.c_str());
			}
		}
		catch (const std::out_of_range& exc)
		{
			result = 0;
		}

	}

	return result;
}

char System::getOperatorFromInput(const MyString& input) const
{
	if (input.length() != 1 || !OPERATORS.contains(input[0]))
		throw std::invalid_argument("Invalid operator!");

	return input[0];
}

void System::handleFormulas()
{
	system("CLS");

	while (true)
	{
		currentTable->print();
		print("Enter the formula you want to use or type \"exit\" to go back\n");
		print("The format should be: = <firstNumber/Cell> <operator> <secondNumber/Cell>\n");
		print("Formula: ");

		std::cin.getline(userInput, MAX_LEN_COMMAND);

		MyVector<MyString> vectorInput = MyString(userInput).split(' ');

		if (vectorInput.getSize() == 1 && vectorInput[0] == commands::EXIT) 
		{
			system("CLS"); 
			return;
		}

		if (vectorInput[0] != "=" || vectorInput.getSize() != 4)
		{
			printMessage(messages::INVALID_FORMAT);
			continue;
		}

		try
		{
			double firstNum = getValueFromInput(vectorInput[1]);
			char formulaOperator = getOperatorFromInput(vectorInput[2]);
			double secondNum = getValueFromInput(vectorInput[3]);

			makeFormula(firstNum, secondNum, formulaOperator);
		}
		catch (const std::exception& exc)
		{
			printMessage(exc.what());
		}
	}
}

bool System::open(const MyString& fileName)
{
	currentTable = new Table;
	currentFile = fileName;

	return currentTable->loadFromFile(currentFile.c_str());
}

void System::printResultFormula(double result) const
{
	print("The result from the formula is: ");
	std::cout << result << std::endl;
	system("pause");
	system("CLS");
}

void System::makeFormula(double firstNum, double secondNum, char formulaOperator) const
{
	switch (formulaOperator)
	{
	case '*':
		printResultFormula(firstNum * secondNum);
		break;
	case '-':
		printResultFormula(firstNum - secondNum);
		break;
	case '+':
		printResultFormula(firstNum + secondNum);
		break;
	case '/':
		if (areEqualDoubles(secondNum, 0))
		{
			printMessage(messages::DIVISION_ZERO);
			break;
		}
		printResultFormula(firstNum / secondNum);
		break;
	case '^':
		if (!isWholeNumber(secondNum))
		{
			printMessage(messages::POW_ERROR);
			break;
		}
		printResultFormula(myPow(firstNum, secondNum));
		break;
	default:
		break;
	}
}

