#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	//9.1 & 9.2 & 9.3
	//Check if file name is provided
	if (argc == 1) {
		std::cerr << "Error: No file name provided\n";
		exit(EXIT_FAILURE);
	}

	//Open input file
	std::string strFileName(argv[1]);
	std::ifstream ifs(strFileName.c_str());

	//Check if input file is open
	if (!ifs.is_open()) {
		std::cerr << "Error: " << strFileName.c_str() 
			<< " could not be opened\n";
		exit(EXIT_FAILURE);
	}

	//Read and display measurements
	std::vector<double> vec;
	for (;;) {
		//Read measurements
		double x;
		ifs >> x;

		//If not valid, ignore measurement
		if (ifs.fail()) {
			ifs.clear();
			ifs.ignore();
		}

		//If valid, display measurement on screen and save in vector
		else {
			std::cout << x << "\n";
			vec.push_back(x);
		}

		//Stop reading when end of file is reached
		if (ifs.eof()) {
			break;
		}
	}

	//Close input file
	ifs.close();

	//Open output file
	std::ofstream ofs(strFileName.c_str());

	//Check if file is open
	if (!ofs.is_open()) {
		std::cerr << "Error: " << strFileName.c_str()
			<< " could not be opened\n";
		exit(EXIT_FAILURE);
	}

	//Find min and max of measurements
	double dMin, dMax;
	dMin = vec[0];
	dMax = vec[0];
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i] > dMax) {
			dMax = vec[i];
		}
		if (vec[i] < dMin) {
			dMin = vec[i];
		}
	}

	//Scale values and write them to output file
	for (int i = 0; i < vec.size(); ++i) {
		ofs << (vec[i] - dMin) / (dMax - dMin) << "\n";
	}

	//Close output file and terminate programme
	ofs.close();
	return 0;
}