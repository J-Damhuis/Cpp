#include <iostream>

int main() {

	/*
	//1.1
	std::cout << "Hello world!\n";
	//The errors were the fact that the functions were unknown due to the fact that
	//iostream had not been included and a semicolon was missing at the end of the line.
	*/

	/*1.2 & 1.3
	//read integers
	std::cout << "Please enter two integer numbers\n";

	int i;
	std::cout << "i = ";
	std::cin >> i;

	int j;
	std::cout << "j = ";
	std::cin >> j;

	//print calculations
	std::cout << "i + j = " << i + j << "\n";
	std::cout << "i - j = " << i - j << "\n";
	std::cout << "i * j = " << i * j << "\n";
	std::cout << "i / j = " << i / j << "\n";
	std::cout << "i % j = " << i % j << "\n";
	//Division only divides to whole numbers. When it is asked to divide by zero
	//it just doesn't do it. Otherwise everything works as expected. The % operator
	//gives the remainder after the initial division.
	*/

	//1.4
	int n;
	std::cout << "Please enter a natural number less than forty: ";
	std::cin >> n;
	std::cout << "Your prime number is: " << (n * n) + n + 41 << "\n";

	return 0;
}