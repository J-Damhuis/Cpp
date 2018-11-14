#include <iostream>

int main() {

	/*
	//2.1 a
	int i = 2 / 5 * 3;
	int j = 3 * 2 / 5;
	std::cout << "i = " << i << std::endl;
	std::cout << "j = " << j << std::endl;

	//2.1 b & c
	int i = static_cast<double>(2) / 5 * 3;
	int j = 2 / 5 * static_cast<double>(3);
	std::cout << "i = " << i << std::endl;
	std::cout << "j = " << j << std::endl;

	//2.2
	double dDouble = 1;
	long double ldDouble = 2;
	int iInt = 3;
	short int siInt = 4;
	long int liInt = 5;
	float fFloat = 6;
	std::cout << "double = " << sizeof(dDouble) << std::endl;
	std::cout << "long double = " << sizeof(ldDouble) << std::endl;
	std::cout << "int = " << sizeof(iInt) << std::endl;
	std::cout << "short int = " << sizeof(siInt) << std::endl;
	std::cout << "long int = " << sizeof(liInt) << std::endl;
	std::cout << "float = " << sizeof(fFloat) << std::endl;
	std::cout << "double * float = " << sizeof(dDouble * fFloat) << std::endl;
	std::cout << "long double * float = " << sizeof(ldDouble * fFloat) << std::endl;
	std::cout << "int * short int= " << sizeof(iInt * siInt) << std::endl;
	std::cout << "short int * long int= " << sizeof(siInt * liInt) << std::endl;
	std::cout << "int * float= " << sizeof(iInt * fFloat) << std::endl;
	std::cout << "double * short int = " << sizeof(dDouble * siInt) << std::endl;
	std::cout << "long int * long double = " << sizeof(liInt * ldDouble) << std::endl;
	std::cout << "double / float * short int = " << sizeof(dDouble / fFloat * siInt) << std::endl;

	//2.3
	int iInt = 1.0;
	double dDouble = 1.6;
	std::cout << static_cast<double>(iInt) << std::endl;
	std::cout << static_cast<int>(dDouble) << std::endl;

	//2.4
	//Get weight and height of person
	double dWeight;
	std::cout << "Please enter your weight in kilograms: ";
	std::cin >> dWeight;
	double dHeight;
	std::cout << "Please enter your height in metres: ";
	std::cin >> dHeight;

	//Calculate BMI and report back
	std::cout << "Your BMI is: " << dWeight / (dHeight * dHeight) << "kg/m^2" << std::endl;
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
	int iDaysLived = 365 * (iCurrentYear - iYearOfBirth) + 30 * (iCurrentMonth - iMonthOfBirth) + iCurrentDay - iDayOfBirth;
	int iYearsLived = iDaysLived / 365;
	std::cout << "Your age is: " << iYearsLived << std::endl;

	//Calculate approximate number of days until next birthday
	int iDaysToNextBirthday = 365 - (iDaysLived % 365);
	std::cout << "Your next birthday is in approximately " << iDaysToNextBirthday << " days" << std::endl;

	return 0;
}