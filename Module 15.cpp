#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>

//Global variables
const int iNrTasks = 2;								//Number of tasks
const int iPopSize = 100;							//Population size
const int iSimulationSteps = 100;					//Number of steps of simulation
const std::vector<double> vecAlpha = {0.8, 0.5};	//Learning task rates
const std::vector<double> vecBeta = {0.3, 0.5};		//Forgetting task rates

//Random number generator
std::mt19937_64 rng;

class Individual {
public:
	Individual();
	std::vector<double> vecPreferences;
	std::vector<int> vecTasksPerformed;
	void performTask(int&);
	void pickTask(std::vector<int>&);
};

Individual::Individual()
{
	for (int i = 0; i < iNrTasks; ++i) {
		vecPreferences.push_back(vecAlpha[i] / iNrTasks * vecBeta[i]);		//Initialising preferences according to formula in manual
	}
}

void Individual::performTask(int &j)
{
	for (int i = 0; i < vecPreferences.size(); ++i) {
		double delta = i == j ? 1.0 : 0.0;
		vecPreferences[i] = (1 - vecBeta[i]) * vecPreferences[i] + delta * vecAlpha[i];
	}
}

void Individual::pickTask(std::vector<int> &jobs)
{
	std::vector<double> vecWeights(jobs.size());											//Declare vector for weights for lottery
	double sum = 0.0;																		//Variable to keep track of sum of weights
	for (int i = 0; i < iNrTasks; ++i) {
		vecWeights[i] = vecPreferences[i] * jobs[i];										//Calculate weights
		sum += vecWeights[i];
	}
	if (sum > 0.0) {																		//If sum of weights is greater than zero
		std::discrete_distribution<int> pickJob(vecWeights.begin(), vecWeights.end());		//Create weighted lottery
		int nextJob = pickJob(rng);															//Choose next job
		performTask(nextJob);																//Make individual perform this job
		jobs[nextJob] -= 1;																	//Remove a vacancy for this job
		vecTasksPerformed.push_back(nextJob);												//Add this job to list of performed jobs
	}
	else {																					//If sum of weights is smaller than zero
		std::uniform_int_distribution<int> pickJob(0, vecWeights.size() - 1);				//Create random picker
		int nextJob = pickJob(rng);															//Choose next job
		performTask(nextJob);																//Make individual perform this job
		jobs[nextJob] -= 1;																	//Remove a vacancy for this job
		vecTasksPerformed.push_back(nextJob);												//Add this job to list of performed jobs
	}
}

void simulate(std::vector<Individual> &vecPopulation)
{
	if (iPopSize % iNrTasks != 0) {															//Check if number of tasks divides neatly into population size
		throw std::logic_error("Not every task has the same number of vacancies\n");
	}
	std::vector<int> vecTasks(iNrTasks, iPopSize / iNrTasks);								//Initialise vector of available tasks

	//Shuffle individuals
	for (int i = vecPopulation.size() - 1; i >= 0; --i) {
		std::uniform_int_distribution<int> pickShuffle(0, i);
		int j = pickShuffle(rng);
		Individual tmp = vecPopulation[i];
		vecPopulation[i] = vecPopulation[j];
		vecPopulation[j] = tmp;
	}

	//Make each individual choose a task
	for (int i = 0; i < vecPopulation.size(); ++i) {
		vecPopulation[i].pickTask(vecTasks);
	}
}

int main()
{
	//Seed rng
	unsigned seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::clog << "Random seed: " << seed << "\n";
	rng.seed(seed);

	//Create population
	std::vector<Individual> vecPopulation(iPopSize);

	try {
		//Simulation
		for (int t = 1; t <= iSimulationSteps; ++t) {
			simulate(vecPopulation);
		}

		//Open output file
		std::ofstream ofs("insects.csv");
		if (!ofs.is_open()) {
			throw std::logic_error("Unable to open output file\n");
		}

		//Write sequences of performed tasks of 3 individuals to output file
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < vecPopulation[i].vecTasksPerformed.size(); ++j) {
				ofs << vecPopulation[i].vecTasksPerformed[j] << "\t";
			}
			ofs << "\n";
		}
		ofs << "\n";

		//Write average probability an individual would switch tasks to output file
		double dAverageSwitch = 0.0;
		for (int i = 0; i < vecPopulation.size(); ++i) {
			for (int j = 0; j < vecPopulation[i].vecTasksPerformed.size() - 1; ++j) {
				if (vecPopulation[i].vecTasksPerformed[j] != vecPopulation[i].vecTasksPerformed[j + 1]) {
					dAverageSwitch += 1.0 / vecPopulation[i].vecTasksPerformed.size();
				}
			}
		}
		ofs << "Population average of switching index = " << dAverageSwitch / iPopSize << "\n";
		ofs.close();
	}
	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}

	return 0;
}

//The individuals only switch tasks with a probability of approximately 0.05. This definitely shows division of labour.