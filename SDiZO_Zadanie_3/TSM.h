#ifndef TSM_H
#define TSM_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <limits>


using namespace std;

class TSM
{
public:
	int numberOfCities;
	int cost;
	vector<int> permutation;
	vector<int> minimumPermutation;

	vector<vector<int>> distancesMatrix;

	TSM();
	~TSM();

	void RunBruteForce();
	void RunGreedyAlgorithm();

	int CalculateCost(vector<int> x);

	void ReadFromFile(string fileName);
};

#endif