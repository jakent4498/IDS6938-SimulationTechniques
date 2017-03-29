#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <functional> 
#include <numeric>     

#include "sobol.hpp"

# define DIM_MAX 2

int dim_num = 1;		// try different values here
int dim_num2 = 2;
float *r;
float *r2;
int seed;
int seed_in;
int seed_out;

int seed2;
int seed2_in;
int seed2_out;

double getQuasiRandomNumber(int *seed)
{
	i4_sobol(dim_num, seed, r);
	return r[0];
}
double getQuasiRandomNumber2(int *seed2)
{
	i4_sobol(dim_num2, seed2, r);
	return r[0];
}


void getNDimQuasiRandomNumber(int *seed, int dim_number, float *r)
{
	i4_sobol(dim_number, seed, r);
}




int main()
{
	r = new float[DIM_MAX];

	//use a random device
	std::random_device rd;
	// Another seed intialization routine (this is just here for future reference for you.)
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	//std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	// 2 different ways to get a random starting seed
	seed = rd();
	seed2 = (rd() + timeSeed)/2;
	//seed2 = timeSeed;



	// 3) Play with N
	unsigned int N = 1000;  // number of values generated
	double randomValue;
	double randomV2;
	std::map<int, int> hist; //Counts of discrete values
	std::vector<double> raw; //raw random values 
	std::vector<double> raw2; //second value


	for (unsigned int i = 0; i < N; ++i) {
		randomValue = 0 + getQuasiRandomNumber(&seed);

		++hist[std::round(randomValue)]; // count the values
		raw.push_back(randomValue);  //push the raw values
	}

	for (unsigned int i = 0; i < N; ++i) {
		randomV2 = 0 + getQuasiRandomNumber2(&seed2);
		raw2.push_back(randomV2);
	}

	for (auto p : hist) {

		// Uncomment if you want to see the values
		//std::cout << std::fixed << std::setprecision(1) << std::setw(2)
		//	<< p.first << " -  "<< p.second << std::endl;

		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "  " << std::string(p.second / (N / 500), '*') << std::endl;

	}


	// Print Results to File
	std::ofstream myfile;
	myfile.open("9histogram_sobol-2D-1000.txt");
	for (auto p : hist) {
		myfile << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "\t" << p.second << std::endl;
	}
	myfile.close();

	myfile.open("9raw_results_sobol-2D-UniformN1000.txt");
	//	for (auto p : raw) {
	for (int i = 0; i<N; i++) {
		double p = raw[i];
		double p2 = raw2[i];

		myfile << std::fixed << std::setprecision(5) << std::setw(2)
			<< p << "," << p2 << std::endl;
	}
	myfile.close();


	//if you choose to write useful stats here
	myfile.open("9useful_stats_sobol-2D-UniformN1000.txt");
	double sum = std::accumulate(raw.begin(), raw.end(), 0.0);
	double mean = sum / raw.size();
	myfile << "mean: " << mean << std::endl;
	std::cout << "mean: " << mean << std::endl;

	std::vector<double> diff(raw.size());
	std::transform(raw.begin(), raw.end(), diff.begin(),
		std::bind2nd(std::minus<double>(), mean));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / raw.size());
	myfile << "stdev: " << stdev << std::endl;
	std::cout << "stdev: " << stdev << std::endl;

	myfile.close();

}