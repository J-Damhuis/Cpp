#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cmath>

//Variables
const int nProtofilaments = 13;		//Number of protofilaments
const int nEvents = 2;				//Number of events
const double tEnd = 0.1;			//Maximum simulation time
const double T = 298.0;				//Temperature
const double kB = 1.3806485E-2;		//Boltzmann constant
const double Kon = 200.0;			//Default elongation rate
const double Koff = 50.0;			//Rate of loss of terminal subunit
const double d = 8.0;				//Length of tubulin heterodimer
double F;
std::mt19937_64 rng;

//Class for protofilaments
class Protofilament {
public:
	Protofilament();
	void updateRates();
	double deltaX;
	std::vector<double> vecRates;
};

//Microtubule
std::vector<Protofilament> Microtubule(nProtofilaments);

Protofilament::Protofilament()
{
	vecRates = std::vector<double>(nEvents);
}

void Protofilament::updateRates()
{
	vecRates[0] = deltaX < 0.0 ? Kon :
		Kon * exp(-(F * deltaX) / (kB * T));		//Sets elongation rate according to deltaX
	vecRates[1] = Koff;								//Sets rate of loss of terminal subunit
}

double simulate()
{
	for (double t = 0.0, length = 0.0;;) {

		//Pool all protofilaments' rates
		std::vector<double> sum = {0.0, 0.0};
		for (int i = 0; i < nProtofilaments; ++i) {
			sum[0] += Microtubule[i].vecRates[0];
			sum[1] += Microtubule[i].vecRates[1];
		}
		
		//Calculate time until next event
		std::exponential_distribution<double> waitingTime(sum[0] + sum[1]);
		t += waitingTime(rng);

		//Decide which event happens
		std::discrete_distribution<int> event(sum.begin(), sum.end());						//Chooses which event happens
		std::vector<double> rates(nProtofilaments);
		for (int i = 0; i < nProtofilaments; ++i) {
			rates[i] = Microtubule[i].vecRates[0];
		}
		std::discrete_distribution<int> protofilamentgrow(rates.begin(), rates.end());		//Chooses which protofilament grows
		std::uniform_int_distribution<int> protofilamentlose(0, 12);						//Chooses which protofilament loses its terminal subunit
		int k;
		switch (event(rng))
		{
		case 0:

			//Decide which protofilament grows
			k = protofilamentgrow(rng);

			//Increase deltaX
			Microtubule[k].deltaX += d;
			break;

		case 1:

			//Decide which protofilament loses its terminal subunit
			k = protofilamentlose(rng);

			//Decrease deltaX
			Microtubule[k].deltaX -= d;
			break;
		}

		//If this protofilament is now the longest
		if (Microtubule[k].deltaX > d) {									
			for (int i = 0; i < nProtofilaments; ++i) {
				if (i != k) {
					Microtubule[i].deltaX -= Microtubule[k].deltaX - d;		//Change deltaX of each protofilament
				}
			}
			length += Microtubule[k].deltaX - d;							//Increase microtubule length
			Microtubule[k].deltaX = d;
		}

		//If this protofilament was the longest
		else if (Microtubule[k].deltaX == 0.0) {							
			double deltaX = 0.0;
			for (int i = 0; i < nProtofilaments; ++i) {						//Find current longest protofilament
				if (Microtubule[i].deltaX > deltaX) {						
					deltaX = Microtubule[i].deltaX;							
				}
			}
			for (int i = 0; i < nProtofilaments; ++i) {
				Microtubule[i].deltaX += d - deltaX;						//Change deltaX of each protofilament
			}
			length -= d - deltaX;											//Decrease microtubule length
		}

		//Calculate new rates
		for (int i = 0; i < nProtofilaments; ++i) {
			Microtubule[i].updateRates();
		}

		//Stop loop and return velocity when max time is reached
		if (t > tEnd) {
			return length / t / 1000;
		}
	}
}

int main()
{
	try {

		//Get seed from system clock
		std::chrono::high_resolution_clock::time_point tp =
			std::chrono::high_resolution_clock::now();
		unsigned seed = static_cast<unsigned>(tp.time_since_epoch().count());
		std::clog << "Random seed: " << seed << "\n\n";
		rng.seed(seed);

		//Open output file
		std::ofstream ofs("Microtubule.csv");
		if (!ofs.is_open()) {
			throw std::logic_error("Unable to open output file\n");
		}

		//Simulate and output results
		for (F = 1E-2; F <= 1E1; F += 1E-2) {

			//Initialise deltaX of protofilaments and update rates
			for (int i = 0; i < nProtofilaments; ++i) {
				Microtubule[i].deltaX = d - i * d / nProtofilaments;
				Microtubule[i].updateRates();
			}

			//Get output from simulation and write to output file
			double velocity = simulate();
			ofs << F << "\t" << velocity << "\n";
		}
		ofs.close();
	}
	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}

	return 0;
}