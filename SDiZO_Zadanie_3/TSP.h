#ifndef TSP_H
#define TSP_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>


using namespace std;

class TSP
{
public:
	int numberOfCities;
	int cost;
	vector<int> permutation;
	vector<int> minimumPermutation;

	vector<vector<int>> distancesMatrix;

	TSP();
	~TSP();

	void RunBruteForce();
	void RunGreedyAlgorithm();

	int CalculateCost(vector<int> x);

	void ReadFromFile(string fileName);
};

#endif