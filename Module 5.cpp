#include <iostream>
#include <vector>
#include <cmath>

int main() {

	/*5.1
	std::cout << "Enter an integer: ";
	int iNumber;
	std::cin >> iNumber;
	for (int i = 1; i <= iNumber; ++i) {
		int j = iNumber % i;
		if (j == 0) {
			std::cout << iNumber << " is divisable by " << i << "\n";
		}
	}
	//Semicolon after for-statement and '=' instead of '==' in if-statement
	*/

	/*5.2
	double r;
	std::cout << "Please enter the intrinsic growth rate: ";
	std::cin >> r;

	double n0;
	std::cout << "Please enter the initial population density : ";
	std::cin >> n0;

	std::vector<double> vec(101, n0);

	for (int i = 1; i < vec.size(); ++i) {
		vec[i] = vec[i - 1] * exp(r * (1 - vec[i - 1]));
	}

	for (int i = 0; i < vec.size(); ++i) {
		std::cout << "N" << i << " = " << vec[i] << "\n";
	}
	*/

	/*5.3
	//Define matrix
	std::vector < std::vector<double> > matrix(4);
	for (int i = 0; i < 4; ++i) {
		matrix[i] = std::vector<double>(4);
	}
	matrix[0][0] = 0;
	matrix[0][1] = 24;
	matrix[0][2] = 26;
	matrix[0][3] = 111;
	matrix[1][0] = 41;
	matrix[1][1] = 0;
	matrix[1][2] = 91;
	matrix[1][3] = 33;
	matrix[2][0] = 35;
	matrix[2][1] = 114;
	matrix[2][2] = 0;
	matrix[2][3] = 34;
	matrix[3][0] = 93;
	matrix[3][1] = 33;
	matrix[3][2] = 27;
	matrix[3][3] = 0;

	//Show matrix
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	//Pool counts
	double dSum = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			dSum += matrix[i][j] += matrix[j][i];
			matrix[j][i] = 0.0;
		}
	}

	//Normalise rates
	for (int i = 0; i < 3; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			matrix[i][j] /= dSum;
		}
	}

	//Estimate relative rates and output them
	const double dTransitions = matrix[0][3] + matrix[1][2];
	std::cout << "Transition rate =   " << dTransitions << "\n"
		<< "Transversion rate = " << 1 - dTransitions << "\n";
	*/

	/*5.4
	for (int iPrimeCandidate = 2, iFactor; iPrimeCandidate < 1000; 
		++iPrimeCandidate) {
		for (iFactor = 2; iFactor <= (iPrimeCandidate / iFactor); ++iFactor) {
			if (!(iPrimeCandidate % iFactor))
				break;
		}
		if (iFactor > (iPrimeCandidate / iFactor)) {
			std::cout << iPrimeCandidate << " is prime\n";
		}
	}

	//a
	//The function checks the first 1000 integers to see whether they're prime

	//b
	//In that case, the last if-statement would not know about the variable iFactor

	//c
	//The expression checks if iPrimeCandidate is divisible by iFactor and if that returns true,
	//break will be executed

	//d
	//If iPrimeCandidate was divisible by an integer larger than sqrt(iPrimeCandidate) then
	//iPrimeCandidate / iFactor would be equal to an integer smaller than sqrt(iPrimeCandidate).
	//In that case, you would have already found it.

	//e
	//It would only evaluate to true if the inner for-loop had been terminated by the loop-condition.
	*/
	
	//5.5
	std::vector<double> vec;
	std::cout << "Please enter positive numbers, "
		"or a negative number to stop.\n";

	//Collect positive numbers until a negative number is entered
	for (;;) {
		std::cout << "Your next input: ";
		double dInput;
		std::cin >> dInput;

		if (dInput < 0.0) {
			break;
		}
		else {
			vec.push_back(dInput);
		}
	}

	//Compute mean
	double dMean = 0.0;
	for (int i = 0; i < vec.size(); ++i) {
		dMean += vec[i];
	}
	dMean /= vec.size();

	//Compute standard deviation
	double dStandardDeviation = 0.0;
	for (int i = 0; i < vec.size(); ++i) {
		dStandardDeviation += pow((vec[i] - dMean), 2);
	}
	dStandardDeviation = sqrt(dStandardDeviation / vec.size());

	//Output results
	std::cout << "The mean of the numbers you entered is:     " 
		<< dMean << "\n" << "The standard deviation of those numbers is: " 
		<< dStandardDeviation << "\n";
	
	/*5.6
	for (int i = 0; i < 5; ++i) {
		std::cout << i << "\n";
	}
	//Outputs numbers 0 to 4
	*/
	
	/*5.7
	int iPrimeCandidate = 2;
	do {
		int iFactor = 2;
		while (iFactor <= (iPrimeCandidate / iFactor)) {
			if (!(iPrimeCandidate % iFactor)) {
				break;
			}
			++iFactor;
		}
		if (iFactor > (iPrimeCandidate / iFactor)) {
			std::cout << iPrimeCandidate << " is prime\n";
		}
		++iPrimeCandidate;
	} while (iPrimeCandidate < 1000);
	*/

	return 0;
}