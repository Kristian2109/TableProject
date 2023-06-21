#include "Table.h"
#include <fstream>
#include <sstream>
#include <exception>
#include "FileFunctions.h"
#include "StringFunctions.h"

const size_t Table::maxCountRows = 10000;
const size_t Table::maxCountColumns = 30;
const size_t Table::maxSizeValue = 256;

Table::Table(const Table& other)
{
	data = other.data;
	maxRowWidth = other.maxRowWidth;
	columnWidths = other.columnWidths;
}
Table& Table::operator=(const Table& other)
{
	data = other.data;
	maxRowWidth = other.maxRowWidth;
	columnWidths = other.columnWidths;

	return *this;
}

MyString Table::loadValue(std::istream& ifs)
{
	char value[maxSizeValue] = "";

	bool willSkipSymbol = false;
	size_t index = 0;
	size_t countParentasies = 0;

	while (true)
	{
		char current = ifs.get();

		if (ifs.eof())
		{
			if (countParentasies % 2 == 1)
			{
				std::cout << "Error: Invalid parentasies!\n";
				throw std::exception(value);
			}
			else 
				break;
		}

		if (willSkipSymbol) { willSkipSymbol = false; }

		else if (current == '\\') { willSkipSymbol = true; }

		else if (current == '"')
			countParentasies ^= 1;

		else if (current == ',' && (countParentasies | 0) == 0)
		{
			value[index] = '\0';
			break;
		}

		if (index == maxSizeValue)
			throw std::out_of_range("Value with more than 256 symbols!");

		value[index++] = current;
	}

	return getCastedString(value);

}

void Table::loadRowFromFile(std::ifstream& inFile, size_t rowIndex)
{
	char buffer[maxCountColumns * maxSizeValue];

	if (inFile.fail())
		throw std::exception("Error while loading from file!\n");

	inFile.getline(buffer, maxCountColumns * maxSizeValue, '\n');
	std::stringstream rowStream(buffer);

	size_t countLoadedValues = 0;

	while (rowStream)
	{
		MyString value = loadValue(rowStream);
	
		data[rowIndex][countLoadedValues++] = value;
	}
}

//Error: row 2, col 5, 123.123.123 is unknown data type

bool Table::loadFromFile(const char* fileName)
{
	std::ifstream inputFile(fileName, std::ios::_Nocreate);

	if (!inputFile.is_open()) { return false; }

	size_t countRowsInFile = getLinesCount(inputFile);
	maxRowWidth = getMaxWidthRowFromFile(inputFile, countRowsInFile);
	columnWidths = MyVector<size_t>(maxRowWidth);

	for (size_t i = 0; i < countRowsInFile; i++)
	{
		data.push_back();

		for (size_t j = 0; j < maxRowWidth; j++)
			data[i].push_back();

		try
		{
			loadRowFromFile(inputFile, i);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Invalid data type on row " << i + 1 << ", column " << exc.what() << std::endl;
			return false;
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error while loading row " << i + 1 << ": " << exc.what() << std::endl;
			return false;
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error while loading row " << i + 1 << ": " << exc.what() << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < maxRowWidth; i++)
	{
		columnWidths.push_back();
		setColumnWidth(i);
	}

	inputFile.close();

	return true;
}

size_t Table::rowsCount() const
{
    return data.getSize();
}

size_t Table::colsCount() const
{
	return maxRowWidth;
}

bool Table::isValueValid(const MyString& value) const
{
	return value.length() <= maxSizeValue;
}
bool Table::isPositionValid(size_t row, size_t col) const
{
	return row < rowsCount() && col < colsCount();
}

const MyString& Table::getValue(size_t row, size_t col) const
{
	if (!isPositionValid(row, col))
		throw std::out_of_range("Row or column out of range!\n");

    return data[row][col];
}

bool Table::setValue(size_t row, size_t col, const MyString& newValue)
{
	if (!isPositionValid(row, col))
		throw std::out_of_range("Row or column out of range!\n");

	if (!isValueValid(newValue))
		throw std::invalid_argument("Exceeded maximum size of value!\n");

    data[row][col] = newValue;
	setColumnWidth(col);

    return true;
}

void Table::addRow()
{
	if (maxCountRows >= rowsCount())
		throw std::out_of_range("Max rows limit reached!");

	data.push_back(Row());
	for (size_t i = 0; i < maxRowWidth; i++)
	{
		data[rowsCount()].push_back();
	}
}
void Table::addColumn()
{
	if (maxCountColumns >= colsCount())
		throw std::out_of_range("Max columns limit reached!");

	for (size_t i = 0; i < rowsCount(); i++)
	{
		data[i].push_back();
	}
}

void Table::setColumnWidth(size_t colIndex)
{
	size_t maxWidthCol = data[0][colIndex].length();

	for (size_t i = 1; i < data.getSize(); i++)
	{
		if (getValue(i, colIndex).length() > maxWidthCol) 
		{
			maxWidthCol = getValue(i, colIndex).length();
		}
	}

	columnWidths[colIndex] = maxWidthCol;
}

void Table::printRow(size_t rowIndex) const
{
	std::cout << "| ";
	for (size_t i = 0; i < data[rowIndex].getSize(); i++)
	{
		printValue(rowIndex, i);
	}

	std::cout << '\n';
}

void Table::printValue(size_t row, size_t col) const
{

	MyString value = getValue(row, col);
	unsigned padding = (columnWidths[col] - value.length()) / 2;

	printSymbol(' ', padding);
	std::cout << value;
	printSymbol(' ', columnWidths[col] - padding - value.length() + 1);
	std::cout << "| ";
}

void Table::print() const
{
	for (size_t i = 0; i < rowsCount(); i++)
	{
		printRow(i);
	}
}

bool Table::saveRowToFile(std::ofstream& outFile, size_t rowIndex) const
{
	if (outFile.fail()) { return false; }

	for (size_t i = 0; i < maxRowWidth; i++)
	{
		MyString value = data[rowIndex][i];

		if (isValidDouble(value.c_str()))
			outFile << value;

		else if (isString(value.c_str()))
		{ 
			MyString toSave = getFormatedStringForSaving(value);

			outFile << '"' << toSave << '"';
		}

		if (i + 1 != maxRowWidth)
			outFile << ',';
	}

	if (rowIndex != rowsCount() - 1) { outFile << '\n'; }
}

bool Table::saveToFile(const char* fileName) const
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) { return false; }

	for (size_t i = 0; i < rowsCount(); i++)
	{
		if (!saveRowToFile(outFile, i)) { return false; }
	}

	return true;
}