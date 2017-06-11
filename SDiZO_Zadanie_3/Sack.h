#ifndef SACK_H
#define SACK_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>


using namespace std;

class Sack
{
public:
	vector<int> values;
	vector<int> weights;
	vector<bool> bruteForceTable;
	int bagCapacity;
	int itemsQuantity;

	Sack();
	~Sack();

	void RunBruteForce();
	void RunGreedyValue();
	void RunGreedyValueRatio();


	void AddOne(int place);
	void ReadFromFile(string fileName);
};

#endif