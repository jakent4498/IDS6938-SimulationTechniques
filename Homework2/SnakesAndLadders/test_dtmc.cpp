#include <iostream>
#include <functional>   
#include <numeric> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <Eigen\dense>

#include "markov.h"
#include "TransitionMatrix.h"


// Hint: Set N - number of simulations low until you have it working
//       Then set it much much higher, and run in release mode so its faster

int main() {

	SetTransitionMatrix();

	// Print Results to File
	std::ofstream myfile;
	myfile.open("markov_results.txt");

	// Print out transition matrix for now
	std::cout << "Transition is " << std::endl << TransitionMatrix << std::endl;
	int start = 0;

	//simulate discrete time Markov Chain
	unsigned int N = 2;
	std::map<int, int> hist;
	std::vector<int> discreteMC;

	for (unsigned int i = 0; i < N; ++i) {
		
		//TODO (add DTMC, and histogram lines.)
		// JAK adding a call to discreteMC, but not sure the right call
//		discreteMC.assign(0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1);
		std::cout << "Starting loop i=" << i << std::endl;
		discreteMC = DTMC(TransitionMatrix, 9, 0);

		// Code if you wanted to print out results at each step
		for (auto elem : discreteMC)
			std::cout << elem << std::endl;

	}
	//Returns an array discreteMC with the states at each step of the discrete-time Markov Chain
	//The number of transitions is given by steps. The initial state is given by start 
	//(the states are indexed from 0 to n-1 where n is the number of arrays in transMatrix).
	//hist is the histogram 


	// (double)p.second / N    - (decimal) percentage.
	for (auto p : hist) {
		std::cout << p.first << "\t" << (double)p.second / N << std::endl;
	}

	myfile.close();

	return 1;
}