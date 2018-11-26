#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>
#include <chrono>

const double pUp = 0.2;
const double pDown = 0.2;
const double pLeft = 0.2;
const double pRight = 0.2;
const int iReefSize = 150;

void updateReef(std::vector<std::vector<int> > &vecReef, std::mt19937_64 &rng)
{
	//Collect positions of food items
	std::vector<std::pair<int, int> > vecFood;
	for (int i = 0; i < vecReef.size(); ++i) {
		for (int j = 0; j < vecReef[i].size(); ++j) {
			if (vecReef[i][j] == 1) {
				vecFood.push_back({i, j});
			}
		}
	}

	//Shuffle coordinate pairs
	for (int i = vecFood.size() - 1; i >= 0; --i) {
		std::uniform_int_distribution<int> pickShuffle(0, i);
		int j = pickShuffle(rng);
		std::pair<int, int> tmp = vecFood[i];
		vecFood[i] = vecFood[j];
		vecFood[j] = tmp;
	}

	//For each food item
	int iConsumedFood = 0;
	for (int i = 0; i < vecFood.size(); ++i) {

		//Pick new position
		if (pDown < 0.0 || pUp < 0.0 || pLeft < 0.0 || pRight < 0.0) {
			throw std::logic_error("Not all probabilities are positive\n");
		}
		if (pDown + pUp + pLeft + pRight > 1.0) {
			throw std::logic_error("Probabilities add up to more than 1\n");
		}
		std::vector<double> vecProbs = {pDown, pUp, pLeft, pRight, 1.0 - pDown - pUp - pLeft - pRight};
		std::discrete_distribution<int> pickNewPos(vecProbs.begin(), vecProbs.end());
		int iNewPos = pickNewPos(rng);
		std::vector<std::pair<int, int> > vecFoodNew = vecFood;
		switch (iNewPos) {
			case 0:		//Food item moves down
				vecFoodNew[i].first = vecFood[i].first + 1;
				break;
			case 1:		//Food item moves up
				vecFoodNew[i].first = vecFood[i].first - 1;
				break;
			case 2:		//Food item moves to the left
				vecFoodNew[i].second = vecFood[i].second - 1;
				break;
			case 3:		//Food item moves to the right
				vecFoodNew[i].second = vecFood[i].second + 1;
				break;
			case 4:		//Food item does not move
				break;
		}

		//Assume boundaries
		if (vecFoodNew[i].first == -1) {
			std::uniform_int_distribution<int> pickNewColumn(0, iReefSize - 1);
			vecFoodNew[i] = {0, pickNewColumn(rng)};
		}
		else if (vecFoodNew[i].second == -1) {
			vecFoodNew[i].second = iReefSize - 1;
		}
		else if (vecFoodNew[i].second == iReefSize) {
			vecFoodNew[i].second = 0;
		}

		//Make coral grow if necessary
		if (vecReef[vecFoodNew[i].first][vecFoodNew[i].second] == 2) {
			vecReef[vecFood[i].first][vecFood[i].second] = 2;
			++iConsumedFood;
		}

		//Move food item to new cell if necessary
		else if (vecReef[vecFoodNew[i].first][vecFoodNew[i].second] == 0) {
			vecReef[vecFoodNew[i].first][vecFoodNew[i].second] = 1;
			vecReef[vecFood[i].first][vecFood[i].second] = 0;
		}

		//Keeping food item at current position is default
	}

	//Add new food items if necessary
	for (int i = 0; i < iConsumedFood; ++i) {
		int j;
		do {
			std::uniform_int_distribution<int> pickNewColumn(0, iReefSize - 1);
			j = pickNewColumn(rng);
		} while (vecReef[0][j] != 0);
		vecReef[0][j] = 1;
	}
}

int main()
{
	/*14.1
	//Get input
	std::vector<int> vecList;
	while (vecList.back() >= 0.0) {
		std::cout << "Enter a positive number (or a negative number to stop): ";
		int dInput;
		std::cin >> dInput;
		vecList.push_back(dInput);
	}

	//Create and seed rng
	std::mt19937_64 rng;
	rng.seed(1);

	std::uniform_int_distribution<int> randomElement(0, vecList.size() - 1);

	//Get output
	std::cout << "Random value chosen is: " << vecList[randomElement(rng)] << "\n";
	*/

	/*14.2
	//Get input
	std::vector<int> vecList;
	do
	{
		std::cout << "Enter a positive number (or a negative number to stop): ";
		int dInput;
		std::cin >> dInput;
		vecList.push_back(dInput);
	} while (vecList.back() > 0);
	vecList.pop_back();

	//Create and seed rng
	std::mt19937_64 rng;
	rng.seed(1);

	//Shuffle
	for (int i = vecList.size() - 1; i > 0; --i) {
		std::uniform_int_distribution<int> randomElement(0, i);
		int j = randomElemtent(rng);
		int tmp = vecList[i];
		vecList[i] = vecList[j];
		vecList[j] = tmp;
	}

	//Output
	std::cout << "The shuffled list is: ";
	for (int i = 0; i < vecList.size(); ++i) {
		std::cout << vecList[i] << ", ";
	}
	std::cout << "\n";
	*/

	/*14.3
	//Define values
	const double b = 2, d = 1, c = 0.001, tEnd = 50.0, dtsav = 1.0;
	int n = 5;

	//Create and seed rng
	std::mt19937_64 rng;
	rng.seed(2);

	//Open output file
	std::ofstream ofs("population.csv");
	if (!ofs.is_open()) {
		std::cerr << "Unable to open output file\n";
		return 1;
	}

	//Output initial state
	std::cout << "0\t" << n << "\n";
	ofs << "0\t" << n << "\n";

	//Simulation
	for (double t = 0.0, tsav = 1.0; t < tEnd;) {

		//Calculate rates
		std::vector<double> vecRates(3);
		vecRates[0] = b * n;
		vecRates[1] = d * n;
		vecRates[2] = c * n * n;

		//Determine time until next event
		double sum = 0.0;
		for (int i = 0; i < vecRates.size(); ++i) {
			sum += vecRates[i];
		}
		std::exponential_distribution<double> waitingTime(sum);
		const double dt = waitingTime(rng);

		//Determine next event
		std::discrete_distribution<int> drawEvent(vecRates.begin(), vecRates.end());
		const int event = drawEvent(rng);

		//Update population state
		t += dt;
		switch (event) {
			case 0:
				++n;
				break;
			case 1:
				--n;
				break;
			case 2:
				--n;
				break;
		}

		//Generate output
		if (t > tsav) {
			std::cout << std::fixed << std::setprecision(0);
			std::cout << t << "\t" << n << "\n";
			ofs << t << "\t" << n << "\n";
			tsav += dtsav;
		}
	}
	*/
	
	//14.4
	try {
		//Obtain seed
		std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
		unsigned seed = static_cast<unsigned>(tp.time_since_epoch().count());

		//Create and seed rng
		std::mt19937_64 rng;
		std::clog << "Random seed: " << seed << "\n";
		rng.seed(seed);

		//Initialise grid
		if (iReefSize < 30) {
			throw std::logic_error("Reef size is too small\n");
		}
		std::vector<std::vector<int> > vecReef(iReefSize, std::vector<int>(iReefSize, 0));
		vecReef[iReefSize - 1] = std::vector<int>(iReefSize, 2);
		std::uniform_int_distribution<int> drawFood(0, iReefSize * (iReefSize - 1) - 1);
		for (int i = 1; i <= 100; ++i) {
			int cell = drawFood(rng);
			if (vecReef[cell / iReefSize][cell % iReefSize] == 1) {
				--i;
			}
			vecReef[cell / iReefSize][cell % iReefSize] = 1;
		}
		std::cout << "Grid initialised\n";

		//Update grid until coral reaches top row
		int iHighestRow = vecReef.size() - 1;
		while (iHighestRow > 0) {
			updateReef(vecReef, rng);
			for (int i = 0; i < vecReef[0].size(); ++i) {
				if (vecReef[iHighestRow - 1][i] == 2) {
					--iHighestRow;
					std::cout << "Coral has reached row " << iHighestRow << "\n";
					break;
				}
			}
		}
		std::cout << "Simulation finished\n";

		//Write end state to output file
		std::ofstream ofs("coral.csv");
		if (!ofs.is_open()) {
			throw std::logic_error("Unable to open output file\n");
		}
		for (int i = 0; i < vecReef.size(); ++i) {
			for (int j = 0; j < vecReef[i].size(); ++j) {
				if (vecReef[i][j] == 1) {
					vecReef[i][j] = 0;
				}
				ofs << vecReef[i][j] << "\t";
			}
			ofs << "\n";
		}
		ofs.close();
	}
	catch (std::exception &error)
	{
		std::cerr << "Error: " << error.what();
		return 1;
	}

	return 0;
}