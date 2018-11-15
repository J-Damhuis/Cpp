#include <iostream>

int main() {

	/*2.1 a
	const int i = 2 / 5 * 3;
	const int j = 3 * 2 / 5;
	std::cout << "i = " << i << "\n";
	std::cout << "j = " << j << "\n";

	//2.1 b & c
	const int i = static_cast<double>(2) / 5 * 3;
	const int j = 2 / 5 * static_cast<double>(3);
	std::cout << "i = " << i << "\n";
	std::cout << "j = " << j << "\n";
	*/

	/*2.2
	const double dDouble = 1;
	const long double ldDouble = 2;
	const int iInt = 3;
	const short int siInt = 4;
	const long int liInt = 5;
	const float fFloat = 6;
	std::cout << "double = " << sizeof(dDouble) << "\n";
	std::cout << "long double = " << sizeof(ldDouble) << "\n";
	std::cout << "int = " << sizeof(iInt) << "\n";
	std::cout << "short int = " << sizeof(siInt) << "\n";
	std::cout << "long int = " << sizeof(liInt) << "\n";
	std::cout << "float = " << sizeof(fFloat) << "\n";
	std::cout << "double * float = " << sizeof(dDouble * fFloat) << "\n";
	std::cout << "long double * float = " << sizeof(ldDouble * fFloat) << "\n";
	std::cout << "int * short int= " << sizeof(iInt * siInt) << "\n";
	std::cout << "short int * long int= " << sizeof(siInt * liInt) << "\n";
	std::cout << "int * float= " << sizeof(iInt * fFloat) << "\n";
	std::cout << "double * short int = " << sizeof(dDouble * siInt) << "\n";
	std::cout << "long int * long double = " << sizeof(liInt * ldDouble) 
		<< "\n";
	std::cout << "double / float * short int = " 
		<< sizeof(dDouble / fFloat * siInt) << "\n";
	*/

	/*2.3
	const int iInt = 1.0;
	const double dDouble = 1.6;
	std::cout << static_cast<double>(iInt) << "\n";
	std::cout << static_cast<int>(dDouble) << "\n";
	*/

	/*2.4
	//Get weight and height of person
	double dWeight;
	std::cout << "Please enter your weight in kilograms: ";
	std::cin >> dWeight;
	double dHeight;
	std::cout << "Please enter your height in metres: ";
	std::cin >> dHeight;

	//Calculate BMI and report back
	std::cout << "Your BMI is: " << dWeight / (dHeight * dHeight) 
		<< "kg/m^2\n";
	*/

	//2.5
	//Create variables
	int iYearOfBirth;
	int iMonthOfBirth;
	int iDayOfBirth;
	int iCurrentYear;
	int iCurrentMonth;
	int iCurrentDay;

	//Get variable values
	std::cout << "Please enter the year in which you were born: ";
	std::cin >> iYearOfBirth;
	std::cout << "Please enter the number of the month in which you were born: ";
	std::cin >> iMonthOfBirth;
	std::cout << "Please enter the day of the month on which you were born: ";
	std::cin >> iDayOfBirth;
	std::cout << "Please enter the current year: ";
	std::cin >> iCurrentYear;
	std::cout << "Please enter the current number of the month: ";
	std::cin >> iCurrentMonth;
	std::cout << "Please enter the current day of the month: ";
	std::cin >> iCurrentDay;
	
	//Calculate age
	const int iDaysLived = 365 * (iCurrentYear - iYearOfBirth) + 
		30 * (iCurrentMonth - iMonthOfBirth) + iCurrentDay - iDayOfBirth;
	const int iYearsLived = iDaysLived / 365;
	std::cout << "Your age is: " << iYearsLived << "\n";

	//Calculate approximate number of days until next birthday
	const int iDaysToNextBirthday = 365 - (iDaysLived % 365);
	std::cout << "Your next birthday is in approximately " 
		<< iDaysToNextBirthday << " days\n";

	return 0;
}