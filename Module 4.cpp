#include <iostream>

int main() {

	/*4.1
	std::cout << "Does the bug fly? Y/N\n";
	char chAnswer1;
	std::cin >> chAnswer1;
	if (chAnswer1 == 'Y') {
		std::cout << "It's an insect\n";
	}
	else {
		std::cout << "Does the bug have 8 legs? Y/N\n";
		char chAnswer2;
		std::cin >> chAnswer2;
		if (chAnswer2 == 'Y') {
			std::cout << "It's a spider\n";
		}
		else {
			std::cout << "Does the bug have 6 legs? Y/N\n";
			char chAnswer3;
			std::cin >> chAnswer3;
			if (chAnswer3 == 'Y') {
				std::cout << "It's an insect\n";
			}
			else {
				std::cout << "Does the bug have no legs? Y/N\n";
				char chAnswer4;
				std::cin >> chAnswer4;
				if (chAnswer4 == 'Y') {
					std::cout << "It's a worm or a larva\n";
				}
				else {
					std::cout << "It might be a millipede\n";
				}
			}
		}
	}
	*/

	/*4.2
	const bool isInputA = true, isInputB = false;
	//a
	if (isInputA > 0) {
		if (isInputB < 1) {
			std::cout << "Hurrah\n";
		}
	}
	else {
		if (isInputB > 0) {
			std::cout << "Hurrah\n";
		}
	}

	//b
	if (isInputA + isInputB > 0 && isInputA + isInputB < 2) {
		std::cout << "Hurrah\n";
	}

	//c
	if (isInputA + isInputB == 1) {
		std::cout << "Hurrah\n";
	}
	*/

	/*4.3
	std::cout << "Which of these colours do you like the most? Red (R), Blue (B) or Yellow (Y)?\n";
	char chAnswer1;
	std::cin >> chAnswer1;
	int iAnswers = 0;
	switch (chAnswer1) {
		case 'R':
			iAnswers += 3;
			break;
		case 'B':
			iAnswers += 1;
			break;
		case 'Y':
			iAnswers += 2;
			break;
	}
	std::cout << "Which of these drinks do you like the most? Water (W), Tea (T) or Coffee (C)?\n";
	char chAnswer2;
	std::cin >> chAnswer2;
	switch (chAnswer2) {
		case 'W':
			iAnswers += 3;
			break;
		case 'T':
			iAnswers += 2;
			break;
		case 'C':
			iAnswers += 1;
			break;
	}
	std::cout << "Which of these animals do you like the most? Lion (L), Horse (H) or Crocodile (C)?\n";
	char chAnswer3;
	std::cin >> chAnswer3;
	switch (chAnswer3) {
		case 'L':
			iAnswers += 1;
			break;
		case 'H':
			iAnswers += 3;
			break;
		case 'C':
			iAnswers += 2;
			break;
	}
	if (iAnswers > 6) {
		std::cout << "You are an optimist\n";
	}
	else if (iAnswers < 6) {
		std::cout << "You are a pessimist\n";
	}
	else {
		std::cout << "You are neither an optimist nor a pessimist\n";
	}
	*/
	
	//4.4
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

	//Calculate x* and return values
	if (a != 0) { //When a is not zero
		if ((b * b) > (4.0 * a * c)) { //2 real-valued solutions
			const double x1 = (-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
			const double x2 = (-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
			std::cout << "x* = " << x1 << ", " << x2 << "\n";
		}
		else if ((b * b) == (4 * a * c)) { //1 real-valued solution
			const double x = -b / (2.0 * a);
			std::cout << "x* = " << x << "\n";
		}
		else { //No real-valued solution
			std::cout << "x* has no real-valued solution\n";
		}
	}
	else if (b != 0) { //When a is zero and b is not zero
		const double x = -c / b;
		std::cout << "x* = " << x << "\n";
	}
	else { //When both a and b are zero
		std::cout << "A solution for x* could not be found\n";
	}
	
	/*4.5
	std::cout << "Please enter a number: ";
	double dVal;
	std::cin >> dVal;

	const double dClip = dVal < 0.0 ? 0.0 : dVal;
	std::cout << dClip << "\n";
	*/
	
	/*4.6
	std::cout << "Who is most resistant to alcohol?\n"
	          << "(1) Master Yoda\n"
	          << "(2) E.T.\n"
	          << "(3) Nefertiti\n"
	          << "(4) Arnold Schwarzenegger\n"
	          << "(5) Jamie Oliver\n"
	          << "    Your answer: ";

	int iAnswer;
	std::cin >> iAnswer;

	switch (iAnswer) {
		case 1: case 2:
			std::cout << "Wrong! (Extraterrestrials don't drink alcohol)\n";
			break;
		case 3:
			std::cout << "Wrong! (Nefertiti only drinks the milk of she-donkeys)\n";
			break;
		case 4:
			std::cout << "Correct!\n";
			break;
		case 5:
			std::cout << "Wrong! (Jamie has a sip of wine now and then, but usually spits it out after tasting)\n";
			break;
		default:
			std::cout << "Invalid answer\n";
			break;
	}
	*/
	
	/*4.7
	const int i = 12, j = 10;

	std::cout << "i & j = " << (i & j) << "\n";
	std::cout << "i | j = " << (i | j) << "\n";
	std::cout << "i ^ j = " << (i ^ j) << "\n";
	std::cout << "~i = " << (~i) << "\n";
	//The & operator gives a 1 in its bits if both i and j have a 1 at that bit
	//The | operator gives a 1 in its bits if at least 1 of i and j has a 1 at that bit
	//The ^ operator gives a 1 in its bits if only 1 of i and j has a 1 at that bit
	//The ~ operator gives a 1 in its bits if i has a 0 at that bit
	*/
	
	return 0;
}