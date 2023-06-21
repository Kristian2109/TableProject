#pragma once
#include "MyVector.h"
#include "Row.h"

class Table
{
	static const size_t maxCountRows;
	static const size_t maxCountColumns;
	static const size_t maxSizeValue;

	MyVector<Row> data;
	size_t maxRowWidth = 0;
	MyVector<size_t> columnWidths;

	void loadRowFromFile(std::ifstream& inFile, size_t rowIndex);
	MyString loadValue(std::istream& ifs);
	bool saveRowToFile(std::ofstream& inFile, size_t rowIndex) const;
	void setColumnWidth(size_t colIndex);
	bool isValueValid(const MyString& value) const;
	bool isPositionValid(size_t row, size_t col) const;

public:
	Table() = default;
	Table(const Table& other);
	Table& operator=(const Table& other);

	size_t rowsCount() const;
	size_t colsCount() const;

	void addRow();
	void addColumn();
	const MyString& getValue(size_t row, size_t col) const;
	bool setValue(size_t row, size_t col, const MyString& newValue);

	bool loadFromFile(const char* fileName);
	bool saveToFile(const char* fileName) const;

	void printValue(size_t row, size_t col) const;
	void printRow(size_t rowIndex) const;
	void print() const;
};

