#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Turtle {
public:
	std::vector<std::vector<double> > vecCoords;	//Matrix of coordinates
	std::vector<double> vecCurrent;					//Vector of current coordinates and heading
	std::vector<std::vector<double> > vecStored;	//Matrix of all stored coordinates and headings
	void doAB();									//Function which does what needs to happen when an A or B is the next character in the sequence
	void doL();										//Function which does what needs to happen when an L is the next character in the sequence
	void doR();										//Function which does what needs to happen when an R is the next character in the sequence
};

void updateString(std::string &string)
{
	for (int i = 0;;) {
		int pos = string.find("A", i);

		//Stop loop when all A's are found
		if (pos == std::string::npos) {
			break;
		}

		//Replace A by BLARA and set start value of next search
		string.replace(pos, 1, "BLARA");
		i = pos + 5;
	}
}

void Turtle::doAB()
{
	vecCoords.push_back({vecCurrent[0], vecCurrent[1]});			//Add current coordinates to matrix
	vecCurrent[0] += cos(2 * M_PI * vecCurrent[2] / 360) *			//Update current x-coordinate
		vecCurrent[3];
	vecCurrent[1] += sin(2 * M_PI * vecCurrent[2] / 360) *			//Update current y-coordinate
		vecCurrent[3];
	vecCoords.push_back({vecCurrent[0], vecCurrent[1]});			//Add updated coordinates to matrix
}

void Turtle::doL()
{
	vecCoords.push_back({});										//Add empty row to matrix
	vecStored.push_back(vecCurrent);								//Store current coordinates and heading
	vecCurrent[2] += 40.0;											//Increase current heading by 40 degrees
	vecCurrent[3] *= 0.8;											//Multiply current vessel length by 0.8
}

void Turtle::doR()
{
	vecCoords.push_back({});										//Add empty row to matrix
	vecCurrent = vecStored.back();									//Go back to most recently stored coordinates and heading
	vecStored.pop_back();											//Clear most recently stored coordinates and heading
	vecCurrent[2] -= 40.0;											//Decrease current heading by 40 degrees
	vecCurrent[3] *= 0.8;											//Multiply current vessel length by 0.8
}

int main()
{
	//Open output file
	std::ofstream ofs("trees.csv");
	if (!ofs.is_open()) {
		std::cerr << "Unable to open output file.\n";
		return 1;
	}

	//Initialise string and output it
	std::string s = "A";
	std::cout << "0\t" << s.size() << "\t" << s << "\n";
	ofs << "0\t" << s.size() << "\t" << s << "\n";

	//Update string n times and output it each step
	const int n = 7;
	for (int i = 1; i <= n; ++i) {
		updateString(s);
		std::cout << i << "\t" << s.size() << "\t" << s << "\n";
		ofs << i << "\t" << s.size() << "\t" << s << "\n";			//I'm using tabs instead of commas because this university laptop's excel uses commas to indicate decimal places
	}
	std::cout << "\n";
	ofs << "\n";

	//Initialise turtle
	Turtle myTurtle;
	myTurtle.vecCurrent = {0.0, 0.0, 0.0, 1.0};						//Starting coordinates are (0, 0) with heading 0 and vessel length 1

	//Move turtle
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == 'A' || s[i] == 'B') {
			myTurtle.doAB();
		}
		else if (s[i] == 'L') {
			myTurtle.doL();
		}
		else if (s[i] == 'R') {
			myTurtle.doR();
		}
		else {
			std::cout << "Skipping unexpected character in string.\n";
		}
	}

	//Output coordinates
	for (int i = 0; i < myTurtle.vecCoords.size(); ++i) {
		std::cout << i + 1 << "\t";
		ofs << i + 1;
		for (int j = 0; j < myTurtle.vecCoords[i].size(); ++j) {
			std::cout << myTurtle.vecCoords[i][j] << " ";
			ofs << "\t" << myTurtle.vecCoords[i][j];
		}
		std::cout << "\n";
		ofs << "\n";
	}
	std::cout << "\n";

	//Close output file and terminate programme
	ofs.close();
	return 0;
}