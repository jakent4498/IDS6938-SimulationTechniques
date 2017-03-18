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

int main(){

	SetTransitionMatrix();

	//Output Vector
	v.setZero();
	v(0) = 1.0;

	// Print Results to File
	std::ofstream myfile;
	myfile.open("markov_results.txt");

	
   // TODO add Markov vector - Matrix multiplication
	std::cout << "Transition is " << std::endl << TransitionMatrix << std::endl;
	std::cout << "v is " << v << std::endl;

	// How to add Markov vector
	//DTMC(v, 1, 6);
 // std::vector<int> DTMC (Eigen::MatrixXf, int, int);
	std::vector<int> discreteMC;
	//discreteMC = DTMC(TransitionMatrix, 1, 1);
	DTMC(TransitionMatrix, 1, 1);

	std::cout << "v2 is " << std::endl;
	for (auto elem : discreteMC) std::cout << elem << std::endl;

	//myfile << v << std::endl;  //this is just a sample, becareful how you print to file so you can mine useful stats
	
	myfile.close();


  return 1;
}