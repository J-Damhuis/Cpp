#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

/*Global variables for 10.5
double dCowNewPrice, dCowExtraPrice, dFoodPrice, dMilkPrice;
*/

/*Structure for 10.1
struct MyStruct {
	int iStructFirst;
	char chStructSecond;
};
*/

/*Class for 10.2
class MyClass {
public:
	void define();
	void print();
private:
	int iClassFirst;
	char chClassSecond;
};
*/

/*Structure for 10.3
struct PhoneData {
	std::string strName;
	int iExtension;
};
*/

//Structure for 10.4
struct ComplexNumber {
	double dReal, dImaginary;
};

/*Class for 10.5
class Farm {
public:
	class Cow {
	public:
		void feed(double);
		double produceMilk();
		double mdFatReserve;
	};
	void invest(double);
	void sellCow(bool);
	void buyCow(bool);
	void buyFood();
	void feedCows();
	void milkCows();
	int getHerdSize();
	double getMoney();
private:
	std::vector<Cow> vecHerd;
	double mdMoney;
};
*/

/*Function for 10.1
void doPrint(const MyStruct &pair)
{
	std::cout << pair.iStructFirst << " " << pair.chStructSecond << "\n";
}
*/

/*Functions for 10.2
void MyClass::define() {
	std::cout << "Please enter an integer: ";
	std::cin >> iClassFirst;
	std::cout << "Please enter a character: ";
	std::cin >> chClassSecond;
}

void MyClass::print() {
	std::cout << iClassFirst << " " << chClassSecond << "\n";
}
*/

/*Function for 10.3
int searchPhoneDirectory(const std::string &strName, 
	const std::vector<PhoneData> &vecPhoneDirectory)
{
	for (int i = 0; i < vecPhoneDirectory.size(); ++i) {
		if (vecPhoneDirectory[i].strName == strName) {
			return vecPhoneDirectory[i].iExtension;
		}
	}
	return 0;
}
*/

//Functions for 10.4
void printValue(const ComplexNumber &z)
{
	std::cout << z.dReal << " + " << z.dImaginary << "i\n";
}

double calcNorm(const ComplexNumber &z)
{
	return sqrt((z.dReal * z.dReal) + (z.dImaginary * z.dImaginary));
}

ComplexNumber calcConjugate(const ComplexNumber &z)
{
	return {z.dReal, -z.dImaginary};
}

ComplexNumber calcProduct(const ComplexNumber &z1, const ComplexNumber &z2)
{
	return {((z1.dReal * z2.dReal) - (z1.dImaginary * z2.dImaginary)), 
		((z1.dReal * z2.dImaginary) + (z1.dImaginary * z2.dReal))};
}

ComplexNumber calcRatio(const ComplexNumber &z1, const ComplexNumber &z2)
{
	ComplexNumber numerator = calcProduct(z1, calcConjugate(z2));
	double denominator = calcNorm(z2) * calcNorm(z2);
	return {(numerator.dReal / denominator), 
		(numerator.dImaginary / denominator)};
}

/*Functions for 10.5
void Farm::Cow::feed(double food)
{
	mdFatReserve += food;
}

double Farm::Cow::produceMilk()
{
	const double milk = 0.05 * mdFatReserve;
	mdFatReserve -= milk;
	return milk;
}

void Farm::invest(double investment)
{
	mdMoney += investment;
}

void Farm::sellCow(bool isEndOfYear = false)
{
	if (isEndOfYear) {
		while (vecHerd.size() > 0) {
			mdMoney += dCowNewPrice + (dCowExtraPrice *
				vecHerd.back().mdFatReserve);
			vecHerd.erase(vecHerd.begin());
		}
	}
	else {
		if (vecHerd.size() > 0) {
			if (mdMoney < 7 * dFoodPrice * vecHerd.size()) {
				mdMoney += dCowNewPrice + (dCowExtraPrice *
					vecHerd.back().mdFatReserve);
				vecHerd.erase(vecHerd.begin());
			}
		}
	}
}

void Farm::buyCow(bool isStartOfYear = false)
{
	if (isStartOfYear) {
		Cow newCow;
		newCow.mdFatReserve = 0.0;
		vecHerd.push_back(newCow);
	}
	else {
		if (mdMoney >= 7.0 * dFoodPrice * vecHerd.size() * 2.0 + dCowNewPrice) {
			Cow newCow;
			newCow.mdFatReserve = 0.0;
			vecHerd.push_back(newCow);
			mdMoney -= dCowNewPrice;
		}
	}
}

void Farm::buyFood()
{
	mdMoney -= dFoodPrice * vecHerd.size();
}

void Farm::feedCows()
{
	for (int i = 0; i < vecHerd.size(); ++i) {
		vecHerd[i].feed(1.0);
	}
}

void Farm::milkCows()
{
	for (int i = 0; i < vecHerd.size(); ++i) {
		mdMoney += dMilkPrice * vecHerd[i].produceMilk();
	}
}

int Farm::getHerdSize()
{
	return vecHerd.size();
}

double Farm::getMoney()
{
	return mdMoney;
}
*/

int main()
{
	/*10.1
	MyStruct pair;
	std::cout << "Please enter an integer: ";
	std::cin >> pair.iStructFirst;
	std::cout << "Please enter a character: ";
	std::cin >> pair.chStructSecond;
	doPrint(pair);
	*/

	/*10.2
	MyClass pair;
	pair.define();
	pair.print();
	*/

	/*10.3
	//Open input file
	std::ifstream ifs("phonedirectory.txt");
	if (!ifs.is_open()) {
		std::cout << "Error: phonedirectory.txt could not be opened\n";
		return 1;
	}

	//Define structure and vector
	std::vector<PhoneData> vecPhoneDirectory;

	//Read data from input file and close input file
	for (;;) {
		std::string strPhoneName;
		ifs >> strPhoneName;

		if (ifs.fail()) {
			break;
		}

		int iPhoneExtension;
		ifs >> iPhoneExtension;

		PhoneData phoneData = {strPhoneName, iPhoneExtension};
		vecPhoneDirectory.push_back(phoneData);
	}
	ifs.close();

	//Allow user to search for a name
	std::cout << "Search for name: ";
	std::string strPhoneName;
	std::cin >> strPhoneName;

	//Search for name and output extension
	if (!searchPhoneDirectory(strPhoneName, vecPhoneDirectory)) {
		std::cout << strPhoneName
			<< " could not be found in this phone directory\n";
	}
	else {
		std::cout << strPhoneName << " has the extension " 
			<< searchPhoneDirectory(strPhoneName, vecPhoneDirectory) << "\n";
	}
	*/

	//10.4
	ComplexNumber z1 = {5.0, 5.0}, z2 = {3.0, -4.0};
	printValue(calcRatio(z1, z2));

	/*10.5
	std::cout << "Please define the next values:\n";
	do {
		std::cout << "The price of a newborn cow : ";
		std::cin >> dCowNewPrice;
	} while (dCowNewPrice <= 0.0);
	do {
		std::cout << "The price of a unit of fat reserve a cow has: ";
		std::cin >> dCowExtraPrice;
	} while (dCowExtraPrice <= 0.0);
	do {
		std::cout << "The price of food to feed one cow for one day: ";
		std::cin >> dFoodPrice;
	} while (dFoodPrice <= 0.0);
	do {
		std::cout << "The price of one unit of milk: ";
		std::cin >> dMilkPrice;
	} while (dMilkPrice <= 0.0);

	double investment;
	do {
		std::cout << "How much money does your farm start with?\n";
		std::cin >> investment;
	} while (investment < 7 * dFoodPrice);
	Farm MyFarm;
	MyFarm.invest(investment);
	MyFarm.buyCow(true);
	
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "\n" << std::left << std::setw(4) << "Day"
		              << std::right << std::setw(5) << "Herd"
		              << std::right << std::setw(8) << "Money" << std::endl;
	
	for (int day = 1; day <= 365; ++day) {
		
		//Buy food
		MyFarm.buyFood();

		//Feed cows
		MyFarm.feedCows();

		//Milk cows and sell milk
		MyFarm.milkCows();
		
		//Every week
		if (!(day % 7)) {

			//Go to market
			MyFarm.buyCow();
			MyFarm.sellCow();

			//Give summary
			std::cout << std::left << std::setw(4) << day
				<< std::right << std::setw(5) << MyFarm.getHerdSize()
				<< std::right << std::setw(8) << MyFarm.getMoney() << "\n";
		}
	}

	//Sell all cows at the end of year
	MyFarm.sellCow(true);
	std::cout << "\nAt the end of the year your farm has a value of " 
		      << MyFarm.getMoney();
	*/

	return 0;
}