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
		int iIncorrectLetters = 0;
		for (int i = 0; i < word.size(); ++i) {
			if (correctLetters.find(word[i]) == std::string::npos) {
				++iIncorrectLetters;
				ch = word[i];
			}
		}
		if (iIncorrectLetters >= 3 && remainingGuesses >= 3) {
			correctLetters.push_back(ch);
			remainingGuesses -= 2;
			std::cout << "You have " << remainingGuesses 
				<< " guesses remaining.\n";
		}
		else {
			std::cout << "Sorry, you're on your own from here on.\n";
		}
	}
	else {
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
		vecWordList[0] = newWord;
	}

	std::string newWord = vecWordList[0];
	for (int i = 1; i < vecWordList.size() / 2; ++i) {
		vecWordList[i - 1] = vecWordList[i];
	}
	vecWordList[vecWordList.size() / 2 - 1] = newWord;

	std::ofstream ofs("hangman_words.txt");
	for (int i = 0; i < vecWordList.size(); ++i) {
		ofs << vecWordList[i] << "\n";
	}
	ofs.close();
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

		//Calculate distances to u
		std::vector<double> u;
		for (int k = 0; k < matrix.size(); ++k) {
			double dIK = iMinQI < k ? matrix[iMinQI][k] : matrix[k][iMinQI];
			double dJK = iMinQJ < k ? matrix[iMinQJ][k] : matrix[k][iMinQJ];
			double dIJ = iMinQI < iMinQJ ? matrix[iMinQI][iMinQJ] : matrix[iMinQJ][iMinQI];
			double dDistanceU = 0.5 * (dIK + dJK - dIJ);
			if (k == iMinQI) {
				double dSum1 = 0.0, dSum2 = 0.0;
				for (int i = 0; i < matrix[k].size(); ++i) {
					dSum1 += iMinQI < i ? matrix[iMinQI][i] : matrix[i][iMinQI];
					dSum2 += iMinQJ < i ? matrix[iMinQJ][i] : matrix[i][iMinQJ];
				}
				double dIJ = iMinQI < iMinQJ ? matrix[iMinQI][iMinQJ] : matrix[iMinQJ][iMinQI];
				dDistanceU = 0.5 * (dIJ + ((dSum1 - dSum2) / (matrix.size() - 2)));
			}
			else if (k == iMinQJ) {
				double dSum1 = 0.0, dSum2 = 0.0;
				for (int i = 0; i < matrix[k].size(); ++i) {
					dSum1 += iMinQI < i ? matrix[iMinQI][i] : matrix[i][iMinQI];
					dSum2 += iMinQJ < i ? matrix[iMinQJ][i] : matrix[i][iMinQJ];
				}
				double dIJ = iMinQI < iMinQJ ? matrix[iMinQI][iMinQJ] : matrix[iMinQJ][iMinQI];
				dDistanceU = 0.5 * (dIJ - ((dSum1 - dSum2) / (matrix.size() - 2)));
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
	}

	//Last step
	double d0 = 0.5 * (matrix[0][1] + matrix[0][2] - matrix[1][2]);
	double d1 = 0.5 * (matrix[0][1] + matrix[1][2] - matrix[0][2]);
	double d2 = 0.5 * (matrix[0][2] + matrix[1][2] - matrix[0][1]);
	std::ostringstream ossNewick;
	ossNewick << "(" << vecSpeciesNames[0] << ":" << d0 << ","
		<< vecSpeciesNames[1] << ":" << d1 << ","
		<< vecSpeciesNames[2] << ":" << d2 << ");";

	//Output to file
	std::ofstream ofs("newick.txt");
	if (!ofs.is_open()) {
		std::cerr << "Error: newick.txt could not be opened\n";
		return 1;
	}
	ofs << ossNewick.str();
	ofs.close();

	return 0;
}