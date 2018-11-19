#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

/*Class for 11.1 & 11.2
class HangmanGame {
public:
	void setSecretWord(const std::string&);
	bool guess(char);
	int getRemainingGuesses();
private:
	std::string word, correctLetters;
	int remainingGuesses;
};
*/

/*Functions for 11.1 & 11.2
void HangmanGame::setSecretWord(const std::string &newWord)
{
	word = newWord;
	correctLetters.clear();
	remainingGuesses = 9;
}

bool HangmanGame::guess(char ch)
{
	if (ch == '?') {
		if (remainingGuesses < 3) {
			std::cout << "You have too few guesses left to request a hint.\n";
			return true;
		}
		int iIncorrectLetters = 0;
		for (int i = 0; i < word.size(); ++i) {
			if (correctLetters.find(word[i]) == std::string::npos) {
				++iIncorrectLetters;
				ch = word[i];
			}
		}
		if (iIncorrectLetters < 3) {
			std::cout << "There are too few characters remaining for you to request a hint.\n";
			return true;
		}
	}
	std::string::size_type found = word.find(ch);
	if (found == std::string::npos) {
		--remainingGuesses;
		std::cout << "Sorry, wrong guess! You have " << remainingGuesses 
			      << " guesses remaining.\n";
		if (remainingGuesses == 0) {
			std::cout << "Too bad... You lost.\n";
			return false;
		}
	}
	else {
		correctLetters.push_back(ch);
	}

	bool isSomeLettersWrong = false;
	std::cout << "\n\tGuessed so far: ";
	for (int i = 0; i < word.size(); ++i) {
		found = correctLetters.find(word[i]);
		if (found == std::string::npos) {
			isSomeLettersWrong = true;
			std::cout << ".";
		}
		else {
			std::cout << word[i];
		}
	}

	if (!isSomeLettersWrong) {
		std::cout << "\n\nCongratulations! You guessed the word.\n";
	}
	else {
		std::cout << "\n\nPlease try again. ";
	}

	return isSomeLettersWrong;
}

int HangmanGame::getRemainingGuesses()
{
	return remainingGuesses;
}
*/

int main()
{
	/*11.1 & 11.2
	std::ifstream ifs("hangman_words.txt");
	if (!ifs.is_open()) {
		std::cerr << "Unable to open input file\n";
		return 1;
	}
	std::vector<std::string> vecWordList;
	for (;;) {
		std::string x;
		ifs >> x;
		if (!ifs.good()) {
			break;
		}
		vecWordList.push_back(x);
	}
	ifs.close();

	HangmanGame hangman;
	hangman.setSecretWord(vecWordList[0]);

	char ch;
	do {
		std::cout << "Enter a letter to guess the secret word (or enter '?' for a hint): ";
		std::cin >> ch;
	} while (hangman.guess(ch));

	if (hangman.getRemainingGuesses()) {
		std::cout << "\nPlease suggest a new word: ";
		std::string newWord;
		std::cin >> newWord;
		
		vecWordList.push_back(vecWordList[0]);
		for (int i = 1; i < vecWordList.size() / 2; ++i) {
			vecWordList[i - 1] = vecWordList[i];
		}
		vecWordList[vecWordList.size() / 2 - 1] = newWord;

		std::ofstream ofs("hangman_words.txt");
		for (int i = 0; i < vecWordList.size(); ++i) {
			ofs << vecWordList[i] << "\n";
		}
		ofs.close();
	}
	*/

	//11.3
	//Open input file
	std::ifstream ifs("distances.txt");
	if (!ifs.is_open()) {
		std::cerr << "Error: distances.txt could not be opened\n";
		return 1;
	}

	//Get number of species
	int iSpeciesNumber;
	ifs >> iSpeciesNumber;

	//Store names of species in vector
	std::vector<std::string> vecSpeciesNames;
	for (int i = 0; i < iSpeciesNumber; ++i) {
		std::string tmp;
		ifs >> tmp;
		vecSpeciesNames.push_back(tmp);
	}
	
	//Create matrix of distances
	std::vector<std::vector<double> > matrix(iSpeciesNumber);
	for (int i = 0; i < iSpeciesNumber; ++i) {
		matrix[i] = std::vector<double>(iSpeciesNumber);
		for (int j = 0; j < iSpeciesNumber; ++j) {
			ifs >> matrix[i][j];
		}
	}

	while (iSpeciesNumber > 3) {

		//Calculate the Q's and put them below the diagonal
		for (int i = 0; i < matrix.size() - 1; ++i) {
			for (int j = i + 1; j < matrix[i].size(); ++j) {
				double dSum1 = 0.0, dSum2 = 0.0;
				for (int k = 0; k < matrix.size(); ++k) {
					dSum1 += k < i ? matrix[k][i] : matrix[i][k];
					dSum2 += k < j ? matrix[k][j] : matrix[j][k];
				}
				matrix[j][i] = (matrix.size() - 2) * matrix[i][j] - dSum1 - dSum2;
			}
		}

		//Show matrix
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[i].size(); ++j) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";

		//Find minimal Q
		double dMinQ = 0.0;
		int iMinQI, iMinQJ;
		for (int i = matrix.size() - 1; i >= 0; --i) {
			for (int j = i - 1; j >= 0; --j) {
				if (matrix[i][j] < dMinQ) {
					dMinQ = matrix[i][j];
					iMinQI = j;
					iMinQJ = i;
				}
			}
		}

		//Print MinQ
		std::cout << "dMinQ = " << dMinQ << "\n"
			<< "iMinQI = " << iMinQI << "\n"
			<< "iMinQJ = " << iMinQJ << "\n\n";

		//Calculate distances to u
		std::vector<double> u;
		for (int k = 0; k < matrix.size(); ++k) {
			double dDistanceU = 0.5 * (matrix[iMinQI][k] + matrix[iMinQJ][k]
				- matrix[iMinQI][iMinQJ]);
			if (k == iMinQI) {
				double dSum1 = 0.0, dSum2 = 0.0;
				for (int i = 0; i < matrix[k].size(); ++i) {
					dSum1 += iMinQI < i ? matrix[iMinQI][i] : matrix[i][iMinQI];
					dSum2 += iMinQJ < i ? matrix[iMinQJ][i] : matrix[i][iMinQJ];
				}
				dDistanceU = 0.5 * (matrix[iMinQI][iMinQJ] + ((dSum1 - dSum2) /
					(matrix.size() - 2)));
			}
			else if (k == iMinQJ) {
				double dSum1 = 0.0, dSum2 = 0.0;
				for (int i = 0; i < matrix[k].size(); ++i) {
					dSum1 += iMinQI < i ? matrix[iMinQI][i] : matrix[i][iMinQI];
					dSum2 += iMinQJ < i ? matrix[iMinQJ][i] : matrix[i][iMinQJ];
				}
				dDistanceU = 0.5 * (matrix[iMinQI][iMinQJ] - ((dSum1 - dSum2) /
					(matrix.size() - 2)));
			}
			u.push_back(dDistanceU);
		}

		//Remove joined columns and rows from matrix
		for (int i = matrix.size() - 1; i >= 0; --i) {
			for (int j = matrix[i].size() - 1; j >= 0; --j) {
				if (j == iMinQI || j == iMinQJ) {
					matrix[i].erase(matrix[i].begin() + j);
				}
			}
			if (i == iMinQI || i == iMinQJ) {
				matrix.erase(matrix.begin() + i);
			}
		}

		//Update Newick tree and clean up species name vector and u
		std::ostringstream ossNewick;
		ossNewick << "(" << vecSpeciesNames[iMinQI] << ":" << u[iMinQI] << ","
			<< vecSpeciesNames[iMinQJ] << ":" << u[iMinQJ] << ")";
		for (int i = vecSpeciesNames.size() - 1; i >= 0; --i) {
			if (i == iMinQI || i == iMinQJ) {
				vecSpeciesNames.erase(vecSpeciesNames.begin() + i);
			}
		}
		vecSpeciesNames.push_back(ossNewick.str());
		for (int i = u.size() - 1; i >= 0; --i) {
			if (i == iMinQI || i == iMinQJ) {
				u.erase(u.begin() + i);
			}
		}
		u.push_back(0.0);

		//Add values of u
		for (int i = 0; i < matrix.size(); ++i) {
			matrix[i].push_back(u[i]);
		}
		matrix.push_back(u);

		--iSpeciesNumber;

		//Show matrix
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[i].size(); ++j) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		for (int i = 0; i < vecSpeciesNames.size(); ++i) {
			std::cout << vecSpeciesNames[i] << " ";
		}
		std::cout << "\n";
		std::cout << ossNewick.str() << "\n";
		std::cout << "\n";
	}

	double d0 = 0.5 * ()

	return 0;
}