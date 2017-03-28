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

using namespace Eigen;
int main(){

	SetTransitionMatrix();

	//Output Vector
	v.setZero();
	v(0) = 1.0;

	// Print Results to File
	std::ofstream myfile;
	myfile.open("markov_results.txt");

	// Add file headers
	myfile << "RowName,";
	for (int i = 0; i < size - 1; i++)
		myfile << "P(" << i << "),";
	myfile << "P("<< (size - 1) <<")" <<std::endl;
	
	//std::cout << "Transition is " << std::endl << TransitionMatrix << std::endl;
	// TODO add Markov vector - Matrix multiplication
	for (int i = 0; i < size; i++) {
		std::cout << "i = " << i << " v is " << v.transpose() << std::endl;
		myfile << "Roll " << i << ",";
		for (int j = 0; j < size-1; j++)
			myfile << v(j) << ",";
		myfile << v(size-1) << std::endl;
		v = v.transpose() * TransitionMatrix;
	}


	//myfile << v << std::endl;  //this is just a sample, be careful how you print to file so you can mine useful stats
	
	myfile.close();

/**/
/*	Matrix3d mat;
	mat << 1, 2, 3, 
		   4, 5, 6, 
		   7, 8, 9;

	std::cout << "Here is mat:\n" << mat << std::endl;
	
	Vector3d u(1, 0, 0), v(2, 0, 4);
	std::cout << "Here is mat*u:\n" << mat*u << std::endl;
	std::cout << "Here is u^T*mat:\n" << u.transpose()*mat << std::endl;
	std::cout << "Here is u^T*v:\n" << u.transpose()*v << std::endl;
	std::cout << "Here is u*v^T:\n" << u*v.transpose() << std::endl;
	std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;
	std::cout << "Let's multiply mat by itself" << std::endl;
	mat = mat*mat;
	std::cout << "Now mat is mat:\n" << mat << std::endl;
*/
  return 1;
}