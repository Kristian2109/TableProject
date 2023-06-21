#include "FileFunctions.h"
#include <sstream>

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
	size_t currentPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	if (!ifs.is_open())
		return 0;

	unsigned int count = 0;

	while (true)
	{
		char current = ifs.get();
		if (ifs.eof())
			break;

		if (current == ch)
			count++;
	}

	ifs.clear();
	ifs.seekg(currentPosition);
	return count;
}

unsigned getCharCountFromRow(std::ifstream& ifs, char ch)
{
	char buffer[1024];
	ifs.getline(buffer, 1024, '\n');
	std::stringstream ss(buffer);

	unsigned int count = 0;

	while (true)
	{
		char current = ss.get();
		if (ss.eof())
			break;

		if (current == ch)
			count++;
	}
	return count;
}

unsigned getLinesCount(std::ifstream& myFile)
{
	return getCharCountFromFile(myFile, '\n') + 1;
}

int findSymbolIndexes(char* str, char symbol)
{
	size_t index = 0;

	while (str[index] != '\0')
	{
		if (str[index] == symbol) { return index; }
		index++;
	}

	return -1;
}

size_t getMaxWidthRowFromFile(std::ifstream& inFile, size_t countRows)
{
	size_t beginPos = inFile.tellg();
	size_t currentMax = getCountWordsInRow(inFile);

	for (size_t i = 1; i < countRows; i++)
	{
		size_t currentCount = getCountWordsInRow(inFile);
		if (currentCount > currentMax) { currentMax = currentCount; };
	}

	inFile.clear();
	inFile.seekg(beginPos);

	return currentMax + 1;
}

size_t getCountWordsInRow(std::ifstream& ifs)
{
	char buffer[1024];
	ifs.getline(buffer, 1024, '\n');
	std::stringstream ss(buffer);

	unsigned int count = 0;
	size_t countParentasies = 0;
	bool willSkipSymbol = false;

	while (true)
	{
		char current = ss.get();

		if (ss.eof())
			break;

		if (willSkipSymbol)
			willSkipSymbol = false;

		else if (current == '\\')
			willSkipSymbol = true;

		else if (current == '"')
			countParentasies ^= 1;

		else if (current == ',' && (countParentasies | 0) == 0)
			count++;
	}
	return count;
}