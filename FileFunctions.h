#pragma once
#include "fstream"

unsigned getCharCountFromFile(std::ifstream& ifs, char ch);

unsigned getLinesCount(std::ifstream& myFile);

size_t getMaxWidthRowFromFile(std::ifstream& inFile, size_t countRows);

size_t getCountWordsInRow(std::ifstream& myFile);