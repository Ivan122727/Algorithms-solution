#include <iostream>
#include "BigInteger.h"

int main()
{
	BigInteger a("12133423242454252352"), b = 13;
	std::cout << a + b << "\n";
	std::cout << a - b << "\n";
	std::cout << a / b << "\n";
	std::cout << a * b << "\n";
	if (a)
	{
		std::cout << "Not equal Zero";
	}
	return 0;
}