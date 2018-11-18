#include <iostream>
#include <string>

/*Functions for 8.2
char tolower(char c)
{
	return c + ('a' - 'A');
}

char toupper(char c)
{
	return c - ('a' - 'A');
}
*/

//Function for 8.3
std::string toRna(const std::string &strDna)
{
	std::string strRna;
	for (int i = strDna.size() - 1; i >= 0; --i) {
		if (strDna[i] == 'A') {
			strRna.push_back('U');
		}
		else if (strDna[i] == 'T') {
			strRna.push_back('A');
		}
		else if (strDna[i] == 'G') {
			strRna.push_back('C');
		}
		else if (strDna[i] == 'C') {
			strRna.push_back('G');
		}
		else {
			std::cout << "Skipping invalid character in DNA sequence\n";
		}
	}
	return strRna;
}

//Function for 8.4
void toCodons(std::string strRna)
{
	//Find start codon
	const int iStartCodon = strRna.find('AUG');

	//No start codon present
	if (iStartCodon == std::string::npos) {
		std::cout << "No start codon could be found\n";
	}

	//Start codon present -> output next codons
	else {
		strRna.erase(0, iStartCodon - 2);
		for (int i = 0; ; i += 3) {
			std::string strCodon = strRna.substr(i, 3);
			std::cout << strCodon << "\n";

			//Check if codon is stop codon and then stop loop
			if (strCodon == "UAG" || strCodon == "UGA" || strCodon == "UAA") {
				break;
			}

			//Stop loop if no stop codon present
			if (i > strRna.size() - 6) {
				std::cout << "Reached end of sequence, stopping translation\n";
				break;
			}
		}
	}
}

int main()
{
	/*8.1
	for (char c = 'a'; c <= 'z'; ++c) {
		std::cout << c << " ";
	}
	*/

	/*8.2
	std::cout << "A -> " << tolower('A') << "\n";
	std::cout << "a -> " << toupper('a') << "\n";
	*/

	/*8.3
	std::string strDna = "CGTCACAGATTAAGGTATACCATT";
	std::cout << strDna << " -> " << toRna(strDna) << "\n";
	*/
	
	//8.4
	std::string strDna = "CGTCACAGATTAAGGTATACCATT";
	std::string strRna = toRna(strDna);
	std::cout << strDna << " -> " << toRna(strDna) << "\n";
	std::cout << "Codons present in this RNA sequence:\n";
	toCodons(strRna);

	return 0;
}