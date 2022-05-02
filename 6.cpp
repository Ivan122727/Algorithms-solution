#include <iostream>
#include "BigInteger.h"

int main()
{
	BigInteger a("12133423242454252352"), b = 13;
	std::cout << a + b << "\n";
	std::cout << a - b << "\n";
	std::cout << a / b << "\n";
	std::cout << a * b << "\n";
	if(a)
	{
		std::cout << "Not equal Zero\n";
	}
	a = 0;
	if (!a)
	{
		std::cout << "Equal Zero\n";
	}
	return 0;
}
