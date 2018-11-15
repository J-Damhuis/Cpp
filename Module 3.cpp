#include <iostream>
#include <cmath>

int main() {

	/*3.1
	int i;
	int j;
	//a
	i = 7;
	i %= 3;
	std::cout << "i = " << i << "\n";

	//b
	i = 7;
	j = i *= 2;
	std::cout << "i = " << i << "\n" << "j = " << j << "\n";

	//c
	j *= (i = 2, j = 4);
	std::cout << "i = " << i << "\n" << "j = " << j << "\n";
	*/

	/*3.2
	int i;
	int j;
	//a
	i = 1;
	j = 4 * (i %= 3 * 2) / 5;
	std::cout << "i = " << i << "\n" << "j = " << j << "\n";

	//b
	i = 1;
	j = 5 * -(i += 5);
	std::cout << "i = " << i << "\n" << "j = " << j << "\n";

	//c
	i = 2;
	j = 2 * (++i)++ / (3 + 2);
	std::cout << "i = " << i << "\n" << "j = " << j << "\n";
	*/

	/*3.3
	double x;
	double t;
	std::cout << "Please enter the time at which you want to know the "
		"tumour's size: ";
	std::cin >> t;
	x = 1.0 * exp(log(0.01 / 1.0) * exp(-0.2 * t));
	std::cout << "The tumour will be " << x << " units large at time " 
		<< t << ".\n";
	//It takes about 22.5 time units for the tumour to reach 95% of its maximum size
	*/

	/*3.4
	const int iInt = 12, iShift = 1;

	const int iResultLeft = iInt << iShift;
	std::cout << "iInt << " << iShift << " = " << iResultLeft << "\n";

	const int iResultRight = iInt >> iShift;
	std::cout << "iInt >> " << iShift << " = " << iResultRight << "\n";
	//The bitshift operators multiply or divide iInt by 2

	const int iResult = iInt / pow(2, 1);
	const int iResult2 = iInt / pow(2, -2);
	const int iResult3 = iInt / pow(2, 3);
	const int iResult4 = iInt / pow(2, -4);
	std::cout << iResult << "\n" << iResult2 << "\n" << iResult3 << "\n" 
		<< iResult4 << "\n";
	*/

	//3.5

	//Get values of variables from keyboard input
	double a;
	std::cout << "a = ";
	std::cin >> a;
	double b;
	std::cout << "b = ";
	std::cin >> b;
	double c;
	std::cout << "c = ";
	std::cin >> c;

	//Calculate x*
	const double x1 = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a);
	const double x2 = (-b - sqrt((b * b) - (4 * a * c))) / (2 * a);

	//Return the values of x*
	std::cout << "x* = " << x1 << ", " << x2 << "\n";

	return 0;
}