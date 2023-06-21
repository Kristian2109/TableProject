#include <iostream>
#include "NumberFunctions.h"

const double EPSILON = 0.0000001;

bool isWholeNumber(double number) {
	if (std::isnan(number) || std::isinf(number)) {
		return false;
	}

	int truncated = number;
	return areEqualDoubles(number, truncated);
}

double myAbs(double number) { return (number > 0) ? number : -number; }

bool areEqualDoubles(double first, double second)
{
	return myAbs(first - second) < EPSILON;
}

double myPow(double number, int power)
{
	double result = 1;

	if (power > 1)
	{
		for (size_t i = 0; i < power; i++)
		{
			result *= number;
		}
	}
	else
	{
		for (int i = 0; i > power; i--)
		{
			result /= number;
		}
	}

	return result;
}

size_t getNearestPowerOfTwo(size_t number)
{
	size_t result = 1;
	for (size_t i = 1; result <= number; i++)
	{
		result *= 2;
	}

	return result;
}
