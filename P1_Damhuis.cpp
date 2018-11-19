//Instead of only making the function able to simulate a cellular automaton according to one rule,
//I made my function able to use all the different rules.

#include <iostream>
#include <vector>
#include <fstream>

//Function to find the value of the k'th bit of number n
int getBit(const int &n, const int &k)
{
	return ((n & (1 << k)) >> k);                              //Move 1 to k'th bit and check if n also has a 1 at this bit
}

int main()
{
	//Get size of vector
	int iVectorSize;                                           //Declare variable for size of vector
	do {
		std::cout << "Please enter the size of the vector: ";  //Ask for size of vector
		std::cin >> iVectorSize;                               //Get size of vector from keyboard
	} while (iVectorSize < 50);                                //Try again if size is too small

	//Get rule
	int iRule;                                                 //Declare variable for rule
	do {
		std::cout << "Please enter the rule you want to use: ";//Ask for rule
		std::wcin >> iRule;                                    //Get rule from keyboard
	} while (iRule < 0 || iRule > 255);                        //Try again if invalid rule (not between 0 and 255)
	
	//Declare and initialise vector
	std::vector<int> vecShells(iVectorSize, 0);                //Vector of specified size with all elements 0
	vecShells[0] = 1;                                          //Set first element to 1

	//Declare and initialise useful variables
	int iUpdateTimes = (3 * iVectorSize) / 2 + 1;              //Set times it should update to be at least 3N/2

	//Open output file
	std::ofstream myOutputFileStream("data.csv");              //Open file named data.csv

	//Write initial states to screen
	std::cout << "0: ";                                        //Write time step at start of line
	for (int i = 0; i < 50; ++i) {                             //Iterate over first fifty elements of vector
		std::cout << vecShells[i] << " ";                      //Write element to screen, followed by space
	}
	std::cout << "\n";                                         //Go to next line after all elements have been written down

	//Update cells
	for (int j = 1; j <= iUpdateTimes; ++j) {                  //Iterate update step at least 3N/2 times

		std::vector<int> vecShellsCopy(vecShells);             //Create copy of vector for updating purposes

		for (int i = 0; i < iVectorSize; ++i) {                //Iterate over all cells in vector

			//Declare and initialise variables for neighbours
			const int iLeft = (i - 1 + iVectorSize) % iVectorSize, iRight = (i + 1) % iVectorSize;
			
			//Set new values in update vector
			/*This is what I had at first, but I found an easier way by getting the second argument for
			//the getBit function from the states of the relevant cells. Thought I'd keep this here so
			//you can see what I did at first.
			if (vecShells[iLeft]) {                            //If left neighbour is 1
				if (vecShells[i]) {                            //If focal cell is 1
					if (vecShells[iRight]) {                   //If right neighbour is 1
						vecShellsCopy[i] = getBit(iRule, 7);   //Set focal cell to new value corresponding to rule
					}
					else {                                     //If right neighbour is 0
						vecShellsCopy[i] = getBit(iRule, 6);   //Set focal cell to new value corresponding to rule
					}
				}
				else {                                         //If focal cell is 0
					if (vecShells[iRight]) {                   //If right neighbour is 1
						vecShellsCopy[i] = getBit(iRule, 5);   //Set focal cell to new value corresponding to rule
					}
					else {                                     //If right neighbour is 0
						vecShellsCopy[i] = getBit(iRule, 4);   //Set focal cell to new value corresponding to rule
					}
				}
			}
			else {                                             //If left neighbour is 0
				if (vecShells[i]) {                            //If focal cell is 1
					if (vecShells[iRight]) {                   //If right neighbour is 1
						vecShellsCopy[i] = getBit(iRule, 3);   //Set focal cell to new value corresponding to rule
					}
					else {                                     //If right neighbour is 0
						vecShellsCopy[i] = getBit(iRule, 2);   //Set focal cell to new value corresponding to rule
					}
				}
				else {                                         //If focal cell is 0
					if (vecShells[iRight]) {                   //If right neighbour is 1
						vecShellsCopy[i] = getBit(iRule, 1);   //Set focal cell to new value corresponding to rule
					}
					else {                                     //If right neighbour is 0
						vecShellsCopy[i] = getBit(iRule, 0);   //Set focal cell to new value corresponding to rule
					}
				}
			}
			*/

			vecShellsCopy[i] = getBit(iRule,                   //Set the new value of the cell to the rule's n'th bit 
				vecShells[iLeft] * 4 +                         //Get n by converting the binary values of the cells to decimal
				vecShells[i] * 2 + vecShells[iRight]));
		}

		//Set vector to update vector
		vecShells = vecShellsCopy;

		//Write to output file (copied from code listing 16.4)
		if (j >= iVectorSize / 2) {                            //At update steps after N/2
			for (int i = 0; i < iVectorSize; ++i) {            //Iterate over whole vector
				myOutputFileStream << vecShells[i] << ",";     //Write element in file, followed by comma
			}
			myOutputFileStream << "\n";                        //Go to next line after whole vector has been written down
		}

		//Write first fifty elements to screen
		std::cout << j << ": ";                                //Write time step at start of line
		for (int i = 0; i < 50; ++i) {                         //Iterate over first fifty elements of vector
			std::cout << vecShells[i] << " ";                  //Write element to screen, followed by space
		}
		std::cout << "\n";                                     //Go to next line after all elements have been written down
	}
	
	//Close output file and terminate programme
	myOutputFileStream.close();                                //Close output file
	return 0;                                                  //Terminate programme
}