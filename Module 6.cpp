#include <iostream>
#include <cmath>
#include <vector>

/*Function for 6.1
double computeNextPopulationDensity(const double &n, const double &r) 
{
	return n * exp(r * (1.0 - n));
}
*/

/*Function for 6.3
void updatePopulationDensity(double &n, const double &r) 
{
	n *= exp(r * (1.0 - n));
}
*/

/*Function for 6.4
double findLargest(const std::vector<double> &vec) 
{
	if (vec.empty()) {
		return -1.0;
	}
	else {
		double dLargest = vec[0];
		for (int i = 1; i < vec.size(); ++i) {
			if (vec[i] > dLargest) {
				dLargest = vec[i];
			}
		}
		return dLargest;
	}
}
*/

//Function for 6.5
void removeDuplicates(std::vector<int> &vec) 
{
	for (int i = 0; i < vec.size(); ++i) {
		for (int j = vec.size() - 1; j > i; --j) {
			if (vec[i] == vec[j]) {
				vec.erase(vec.begin() + j);
			}
		}
	}
}

/*Functions for 6.6
void reportRunningAverage(const double &dWeight) 
{
	static double dSum = 0.0;
	static int n = 0;

	dSum += dWeight;
	++n;

	std::cout << "The running average of the values entered thus far is: " 
		<< dSum / n << "\n";
}

bool isValidInput() 
{
	std::cout << "Next value: ";
	double dWeight;
	std::cin >> dWeight;
	if (dWeight < 0.0) {
		return false;
	}
	else {
		reportRunningAverage(dWeight);
		return true;
	}
}
*/

/*Function for 6.7
int calcFactorial(const int &iNumber) 
{
	return iNumber == 0 ? 1 : iNumber * calcFactorial(iNumber - 1);
}
*/

/*Function for 6.8
double pow(const int &x, const int &n) 
{
	if (n < 0) {
		return 1.0 / pow(x, -n);
	}
	else if (n == 0) {
		return 1.0;
	}
	else if (n > 0 && n % 2) {
		return x * pow(x, n - 1);
	}
	else {
		return pow(x, n / 2) * pow(x, n / 2);
	}
}
*/

int main() {

	/*6.1
	double r;
	std::cout << "Please enter the intrinsic growth rate: ";
	std::cin >> r;

	double n0;
	std::cout << "Please enter the initial population density : ";
	std::cin >> n0;

	std::vector<double> vec(101, n0);

	for (int i = 0; i < (vec.size() - 1); ++i) {
		vec[i + 1] = computeNextPopulationDensity(vec[i], r);
		std::cout << "N" << i << " = " << vec[i] << "\n";
	}
	std::cout << "N" << (vec.size() - 1) << " = " << vec[vec.size() - 1] 
		<< "\n";
	*/

	/*6.2
	//My prediction of the output:
	//i = 0; j = 0
	//i = 1; j = 1
	//i = 2; j = 2
	int i = 0;
	int &j = i;
	std::cout << "i = " << i << "; j = " << j << "\n";
	++j;
	std::cout << "i = " << i << "; j = " << j << "\n";
	++i;
	std::cout << "i = " << i << "; j = " << j << "\n";
	//I was right
	*/

	/*6.3
	//The function just needs read access so using const-reference is correct
	double r;
	std::cout << "Please enter the intrinsic growth rate: ";
	std::cin >> r;

	double n0;
	std::cout << "Please enter the initial population density : ";
	std::cin >> n0;

	std::vector<double> vec(101, n0);

	for (int i = 0; i < (vec.size() - 1); ++i) {
		double n = vec[i];
		updatePopulationDensity(n, r);
		vec[i + 1] = n;
		std::cout << "N" << i << " = " << vec[i] << "\n";
	}
	std::cout << "N" << (vec.size() - 1) << " = " << vec[vec.size() - 1] 
		<< "\n";
	*/

	/*6.4
	std::cout << "Enter positive numbers to add them to a list, "
		"and enter a negative number to finish the list\n";
	std::vector<double> vec;

	//Take inputs
	for (;;) {
		std::cout << "Your next input: ";
		double dInput;
		std::cin >> dInput;
		if (dInput < 0) {
			break;
		}
		else {
			vec.push_back(dInput);
		}
	}

	//Find largest number and output it
	if (findLargest(vec) == -1) {
		std::cout << "There are no elements on the list\n";
	}
	else {
		std::cout << "The largest element on this list is: " 
			<< findLargest(vec) << "\n";
	}
	*/

	//6.5
	std::cout << "Enter positive numbers to add them to a list, and enter a " 
		         "negative number to stop adding numbers to the list\n";
	std::vector<int> vec;

	//Take inputs
	for (;;) {
		std::cout << "Your next input: ";
		int dInput;
		std::cin >> dInput;
		if (dInput < 0) {
			break;
		}
		else {
			vec.push_back(dInput);
		}
	}

	//Remove duplicates and output new vector
	removeDuplicates(vec);
	std::cout << "The list contains the unique values: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
	
	/*6.6
	std::cout << "Enter a series of weight measurements, "
		"or a negative number to stop\n";
	while (isValidInput());
	*/
	
	/*6.7
	//Iterative
	int iNumber;

	//Get the number
	do {
	std::cout << "Enter a whole positive number: ";
	std::cin >> iNumber;
	} while (iNumber < 0);

	int iFactorial = 1;

	//Calculate factorial
	for (int i = 1; i <= iNumber; ++i) {
		iFactorial *= i;
	}

	//Output factorial
	std::cout << iNumber << "! = " << iFactorial << "\n";
	
	//Recursive
	int iNumber;

	//Get the number
	do {
		std::cout << "Enter a whole positive number: ";
		std::cin >> iNumber;
	} while (iNumber < 0);

	//Calculate factorial and output it
	std::cout << iNumber << "! = " << calcFactorial(iNumber) << "\n";
	*/
	
	/*6.8
	std::cout << "2^-4 = " << pow(2, -4) << "\n";
	std::cout << "2^-4 = " << pow(2.0, -4.0) << "\n";
	*/
	
	return 0;
}