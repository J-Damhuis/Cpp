/*12.1
//It first checks if f(a) and f(b) differ in sign (if their product is negative)
//If this is not the case, it sends an error message
//Otherwise, it first makes sure that f(a) is equal to or smaller than 0
//As long as the difference between a and b is large enough:
	//Check if f(the average of a and b) is equal to or smaller than 0
	//If this is the case, set a to the average of a and b
	//Otherwise set b to the average of a and b
//Output the average of a and b
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <iomanip>

/*Variables for 12.2
const int iOffspring = 1000;
const double s = 0.01;
const double mu = 0.001;
*/

/*Structure for 12.2
struct Individual {
	bool isWTAllele, isAlive;
};
*/

/*Vector for 12.2
std::vector<Individual> population(iOffspring, {true, true});
*/

/*Functions for 12.1
double executeFunction(double &x)
{
	return ((x * x) - 2);
}

double findRoot(double &a, double &b)
{
	double fa = executeFunction(a), fb = executeFunction(b);
	if (fa * fb <= 0) {
		if (fa > 0.0) {
			double tmp = a;
			a = b;
			b = tmp;
		}
		double epsilon = 1.0e-6;
		int iCount = 0;
		for (; abs(a - b) > epsilon; ) {
			double c = (a + b) / 2;
			if (executeFunction(c) <= 0) {
				a = c;
			}
			else {
				b = c;
			}
			++iCount;
			if (iCount >= 100) {
				throw(std::logic_error("Took too long to find the root of the function"));
			}
		}
		return (a + b) / 2;
	}
	else {
		throw std::logic_error("Root of the function is not in this range.\n");
	}
}
*/

/*Functions for 12.2
void mutation()
{
	for (int i = 0; i < population.size(); ++i) {
		if (population[i].isWTAllele && std::rand() < mu * RAND_MAX) {
			population[i].isWTAllele = false;
		}
	}
}

void selection()
{
	for (int i = 0; i < population.size(); ++i) {
		if (population[i].isWTAllele && std::rand() < s * RAND_MAX) {
			population[i].isAlive = false;
		}
		else {
			population[i].isAlive = true;
		}
	}
}

void removeDeadIndividuals()
{
	for (int i = 0; i < population.size(); ++i) {
		if (!population[i].isAlive) {
			population[i] = population.back();
			population.pop_back();
			--i;
		}
	}
}

void produceOffspring()
{
	assert(population.size() > 0);
	std::vector<Individual> offspring;
	for (int i = 0; i < iOffspring; ++i) {
		const int j = i % population.size();
		assert(population[j].isAlive);
		offspring.push_back(population[j]);
	}
	population = offspring;
}

void showData(int t)
{
	int cnt = 0;
	for (int i = 0; i < population.size(); ++i) {
		if (!population[i].isWTAllele) {
			++cnt;
		}
	}
	std::cout << t << " " << cnt * 1.0 / population.size() << "\n";
}
*/

int main()
{
	/*12.1
	try {
		double a = -1.0, b = -2.0;
		std::cout << "The root of the function is: " << findRoot(a, b) << "\n";
	}
	catch (std::exception &error)
	{
		std::cerr << "Error: " << error.what() << "\n";
		return 1;
	}
	*/

	/*12.2
	std::srand(127264);
	for (int t = 0; t < 1000; ++t) {
		mutation();
		selection();
		removeDeadIndividuals();
		produceOffspring();
		showData(t);
	}
	*/

	//12.4
	//Initial parameter values
	const double dVt = 0.1, dVp = 0.1, dCpt = 0.06, dCt = 0.5, dCp = 0.02, 
		dT0 = 0.0, dP0 = 0.05, dMaxGenerations = 1000;

	try {
		//Check for proper values
		if (dVt < 0.0 || dVp < 0.0) {
			throw(std::logic_error("Variance is negative.\n"));
		}
		if (fabs(dCpt) > sqrtf(dVt + dVp)) {
			throw(std::logic_error("Covariance is out of bounds.\n"));
		}

		//Initialise G
		std::vector<std::vector<double> > vecG(2, std::vector<double>(2));
		vecG[0][0] = dVt;
		vecG[0][1] = vecG[1][0] = dCpt;
		vecG[1][1] = dVp;

		//Set initial trait values
		std::vector<double> vecZ{ dT0, dP0 };

		//Output initial state
		std::cout << std::fixed << std::setprecision(4);
		std::cout << std::left << std::setw(5) << "time"
			<< std::right << std::setw(8) << "trait"
			<< std::setw(8) << "pref" << std::endl;
		std::cout << std::left << std::setw(5) << "0"
			<< std::right << std::setw(8) << vecZ[0]
			<< std::setw(8) << vecZ[1] << std::endl;

		//Iteration loop
		for (int t = 1; t <= dMaxGenerations; ++t) {
			//Compute selection gradient vector
			std::vector<double> vecBeta(2);
			vecBeta[0] = vecZ[1] - dCt * vecZ[0];
			vecBeta[1] = -dCp * vecZ[1];

			//Multiply selection gradient vector with G to get deltaZ
			double dDeltaT = vecBeta[0] * (vecG[0][0] + vecG[0][1]);
			double dDeltaP = vecBeta[1] * (vecG[1][0] + vecG[1][1]);

			//Update mean trait values
			vecZ[0] += dDeltaT;
			vecZ[1] += dDeltaP;

			//Output current state
			std::cout << std::left << std::setw(5) << t
				<< std::right << std::setw(8) << vecZ[0]
				<< std::setw(8) << vecZ[1] << std::endl;
		}
	}
	catch (std::exception &error)
	{
		std::cerr << "Error: " << error.what() << "\n";
		return 1;
	}

	return 0;
}

//12.4.a
//The strength of female preference decreases steadily, whereas the exaggeration of a male
//ornament initially increases quite quickly and then decreases steadily as well.
//Costly preferences cannot be maintained.

//12.4.b
//My conclusions do not change

//12.4.c
//In the model, female preference cannot be maintained. Sexually selected traits are often highly
//exaggerated and costly. This suggests that female preference is not exaggerated enough?

//12.4.d
//For some species there is such a positive genetic covariance.
//
//The genetic covariance gets built up by the fact that males with costly ornaments usually have
//a higher fitness, which can be passed on to the offspring. Females with a stronger preference
//for these males would produce offspring with higher fitness, and so the genes for this strong
//preference become more abundant in the population.
//
//The genetic covariance decays over time due to other females finding another way to increase
//the fitness of their offspring, such as a strong preference for a different male trait, which
//is indicative of high male fitness.
//It can also decay over time if the male ornament is no longer indicative of high fitness.